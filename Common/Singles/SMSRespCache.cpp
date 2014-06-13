////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMSRespCache.cpp
// Modifyed by Pavel Alexeev
// ��� ������ ����� �������� �������
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMSRespCache.h"
#include "../../Utils/lock.h"

#include "../../SMS/OutSMS.h"

#include "singleton.h" //��� ����� ����

////////////////////////////////////////////////////////

#include <algorithm>

////////////////////////////////////////////////////////
class CSMSRespCacheImpl : public ISMSRespCache{
public:
	CSMSRespCacheImpl();
	virtual ~CSMSRespCacheImpl();

	//������������ ������������� ���������
	virtual void Initialize(CWnd * w);
	//��� ����� ����� �����, �������� ��� ������ ��������, ��� ������ ����������
	virtual void Initialize();

	virtual void AddSMS( CH<IOutSMS> sms );
	virtual void AddRESP( SP<IPDUSubmitSmResp> resp );
	//�������� ��� �������������� ����������, ��� ���� ������ ��� ������, ��������� �� �������� ���������.
	virtual void FlushAllCacheToFailed();

	virtual CH<IOutSMS> GetSendedSMS () /*throw (IOutSMS::Empty)*/;
	virtual CH<IOutSMS> GetFailedSMS () /*throw (IOutSMS::Empty)*/;

	virtual size_t Size();

	virtual void CommitError();
	virtual void UnCommitError();
protected:
	OutSMSlist		m_CachedSMSs;		//�������� ���������
	OutSMSlist		m_CachedSendedSMSs;	//������� ������������, � ��  ��� ����� ���������� 0 �����
	SequenceList	m_NullResps;		//������ (Sequence) RESP'��, ������� ��� ������ �� �����
	RespsList		m_RespWithoutSMS;	//�����, ��� ������� � ���� ������ ���� ���� ����� (�������� ��� ������� �� ��������� ������)

	CH<IOutSMS>		m_LastFailedSMS;	//����� ��� �������� �� ������ ������ �� *CommitError
	bool m_LastFailedSMSactive;			//������������� �� �������� � �������� ����

private:
	//����, �������� ����� ����� ��������� ��� ��������� ������� �� �������� ���
  	HWND WM_messageRecipient;
	CWnd * WM_messageRecipientCWND;
	virtual void SendMessageCache (int msg);

	CLock m_Lock;

	//�����-������� ��� ��������� � ������ ������ SMS, � ����������� � ��� resp'�
	class SMSAddRespCMP {
	friend class ISMSRespCache;
	public:
		SMSAddRespCMP(const CH<IPDUSubmitSmResp> p) : _newResp(p) { }
		bool operator() (CH<IOutSMS> CMPsms) const {
		//SMS�� ���� ����, ���� ������� � ����, � ������ ���������
		return CMPsms->AddRESP(_newResp);
		}
	private:
	const CH<IPDUSubmitSmResp> _newResp;
	};

	//�����-������� ��� ������ _��������_ ������������ �����
	class SMSFailedRespCMP {
	public:
		bool operator() (CH<IOutSMS> CMPsms) const {
		return (CMPsms->getCountFailPDUs() > 0);
		}
	};

	//��������� SP<IPDUSubmitSmResp> �� ��� SequenseNumber
	class CMPRespBySeqN {
	public:
		CMPRespBySeqN (DWORD cmp) : _cmp(cmp){};
		bool operator() (CH<IPDUSubmitSmResp> & CMPresp) const {
		return (CMPresp->GetSequenceNumber() == _cmp);
		}
	private:
		DWORD _cmp;
	};
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMSRespCache, CSMSRespCacheImpl )

////////////////////////////////////////////////////////
CSMSRespCacheImpl::CSMSRespCacheImpl() : WM_messageRecipient (0), m_LastFailedSMSactive (false)
{
}

////////////////////////////////////////////////////////
CSMSRespCacheImpl::~CSMSRespCacheImpl()
{
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::Initialize(){
CLocalLock lock( m_Lock );

//������������ �����-�� ��������, �� ������� ���� ��� ��������
FlushAllCacheToFailed();
Sleep(2000);//����� ���� ����������� ����������. ��������� �� �����, �������.

m_CachedSMSs.clear();
m_CachedSendedSMSs.clear();
m_NullResps.clear();
m_RespWithoutSMS.clear();

m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::Initialize(CWnd * w){
CLocalLock lock( m_Lock );
WM_messageRecipientCWND = w;
//������ ��� ������� �������
Initialize();
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::FlushAllCacheToFailed(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::FlushAllCacheToFailed()");
//��� ���������� �������� ����������
OutSMSlist::iterator allI = m_CachedSMSs.begin();

	while (allI != m_CachedSMSs.end()){
	(*allI)->MarkBad (ESME_FLUSHERR);//ESME_FLUSHERR ������ � ��� �����������
	}

//� ���� ����������� ��������� �� �� ���������
SendMessageCache(WM_SMPP_SUBMIT_RESP_FAILED);
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::AddSMS( CH<IOutSMS> sms ){
CLocalLock lock( m_Lock );

m_CachedSMSs.push_back(sms);
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::AddRESP( SP<IPDUSubmitSmResp> respSP ){
CLocalLock lock( m_Lock );

//-70 �������� ��� ������, ����� ����� �����, ��� �� ������� ����� �������� CH<>...
CH<IPDUSubmitSmResp> resp; resp->Initialize(respSP->GetRawData(), respSP->GetInSocket());

OutSMSlist::iterator fi = std::find_if(m_CachedSMSs.begin(), m_CachedSMSs.end(), SMSAddRespCMP(resp));

	if (fi != m_CachedSMSs.end()){//������ �������, � ������������
	//��������� ����� �� ��� �� ����� ���������, � ������ �� ������ �� ���������� ���
		if ( (*fi)->getCountFailPDUs() == 0 ){//���� ��
			//�������� �������� ������ ���
			if ( ((*fi)->RespComplete()) && ((*fi)->getCountOkPDUs() == (*fi)->getCountPDUs() )) {
			//��������! ����������, ����� � ��������� ��� � ��� ������ �� ��������!
			m_CachedSendedSMSs.splice(m_CachedSendedSMSs.end(),m_CachedSMSs, fi); 
			//�� � ���� ��������� ��������� ���� ��� ����� ���� ������ ������������:
			SendMessageCache(WM_SMPP_SUBMIT_RESP_SENDED);
			}			
		}
		else{//������
		SendMessageCache(WM_SMPP_SUBMIT_RESP_FAILED);
		}		
	}
	else{//�� �������.
	//����� ����, ����� ���� ���� resp ������ �� �����
	SequenceList::iterator si = std::find(m_NullResps.begin(), m_NullResps.end(), resp->GetSequenceNumber() );
		if (si != m_NullResps.end()){//�� �����
		m_NullResps.erase(si);
		}
		else{//����� ������ ����� ��� ������ ���� ������� ��� ���������, ����������, � ��������� �������������� SMS
		m_RespWithoutSMS.push_back(resp);
		}
	}
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::SendMessageCache (int msg){
CLocalLock lock( m_Lock );
//-87
	if (!WM_messageRecipient) WM_messageRecipient = WM_messageRecipientCWND->GetSafeHwnd();
//-87
	::PostMessage( WM_messageRecipient, WM_COMMAND, msg, 0);
}

////////////////////////////////////////////////////////
//�� ����� ������, � ���������, ����� - throw new IOutSMS::Empty
CH<IOutSMS>
CSMSRespCacheImpl::GetSendedSMS (){
CLocalLock lock( m_Lock );

	if (!m_CachedSendedSMSs.empty()){
	CH<IOutSMS> retVal = m_CachedSendedSMSs.front();
	m_CachedSendedSMSs.pop_front();
	return retVal;
	}
	else throw new IOutSMS::Empty;
}

////////////////////////////////////////////////////////
//�� ����� ������, � ���������, ����� - throw new IOutSMS::Empty
CH<IOutSMS>
CSMSRespCacheImpl::GetFailedSMS (){
CLocalLock lock( m_Lock );

//������ ���� ������� *CommitError ��� ��� ����� �� ���������� ������
chASSERT ( !m_LastFailedSMSactive );

//ISMSRespCache::
OutSMSlist::iterator fs = std::find_if(m_CachedSMSs.begin(), m_CachedSMSs.end(), SMSFailedRespCMP());
	
	if (fs != m_CachedSMSs.end()){//������ �������, � ������������
	m_LastFailedSMS = *fs;
	m_CachedSMSs.erase(fs);
	m_LastFailedSMSactive = true;
	return m_LastFailedSMS;
	}
	else throw new IOutSMS::Empty;//�� ������� ������
}

////////////////////////////////////////////////////////
//����������� ������, ���, ������ �� ���� ������������ ����� ���� ���
void
CSMSRespCacheImpl::CommitError(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::CommitError()");

//������ ����!
chASSERT ( m_LastFailedSMSactive );

/*�����������, ������ ��� ��� ���������� ����� ������� �� m_RespWithoutSMS
� ���������� (������� �� ���� � m_RespWithoutSMS) ��������� � m_NullResps
*/
//������ �� ���� ���, � ������� ���� ������, ������ �� ��� ����� ��������� ��� �����
IOutSMS::SMSPairVector::iterator pairI = m_LastFailedSMS->GetPDUs().begin();
	while (pairI != m_LastFailedSMS->GetPDUs().end()){
		if (pairI->second->GetSequenceNumber() == NOT_RESP_SEQ){//������ ���� �� ��� �������
		//������ _��� ����_ ������� �����, �������� �������
		RespsList::iterator withoutIter = std::find_if(m_RespWithoutSMS.begin(), m_RespWithoutSMS.end(), CMPRespBySeqN(pairI->second->GetSequenceNumber()));
			if (withoutIter != m_RespWithoutSMS.end()){//������ ������
			m_RespWithoutSMS.erase(withoutIter);
			}
			else{//������ �� ������, ��������� � ��������
			m_NullResps.push_back(pairI->second->GetSequenceNumber());
			}
		}
	++pairI;
	}

m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
//�� �����������, ������� �� �� ��������� � �������� ������. �������� ��� ��� ��� ��������. �������� ����������� ��������� ����� �����.
void
CSMSRespCacheImpl::UnCommitError(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::UnCommitError()");

chASSERT ( m_LastFailedSMSactive );
/*�� �����������, ������ ������� (�������� ����������, ��� �� ������ ������������) �����
� ��� �������� ������ �����, ���������, �� ������ �� �� ��� ����� � ��� �����-�� ������ � m_RespWithoutSMS
*/

//������ �� ���� ���, � ������� ���� ������, ������ �� ��� ����� ��������� ��� �����
IOutSMS::SMSPairVector::iterator pairI = m_LastFailedSMS->GetPDUs().begin();
	while (pairI != m_LastFailedSMS->GetPDUs().end()){
		if (pairI->second->GetSequenceNumber() == NOT_RESP_SEQ){//������ ���� �� ��� �������
		//������ _��� ����_ ������� �����, �������� �����������
		RespsList::iterator withoutIter = std::find_if(m_RespWithoutSMS.begin(), m_RespWithoutSMS.end(), CMPRespBySeqN(pairI->second->GetSequenceNumber()));
			if (withoutIter != m_RespWithoutSMS.end()){//������ ������
			m_LastFailedSMS->AddRESP(*withoutIter);
			m_RespWithoutSMS.erase(withoutIter);
			}
//����� ������� ������� ���� ���� ���������, ������ ��� ��� ����� �����, � �������� ���������...
//		m_CachedSendedSMSs.splice(m_CachedSendedSMSs.end(),m_CachedSMSs, fi); 
		}
	++pairI;
	}

//AddSMS(m_LastFailedSMS); ������, ��� �������������
//�� � ������� ��� � ��������
m_CachedSMSs.push_back(m_LastFailedSMS);
m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
size_t
CSMSRespCacheImpl::Size(){
return m_CachedSMSs.size();
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////