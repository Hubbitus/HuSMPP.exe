////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMSRespCache.h
// Modifyed by Pavel Alexeev
// ��� ������ ����� �������� �������
//
//	2008-09-18
//	- Added method Size()
////////////////////////////////////////////////////////

#ifndef __SMSRespCache_H__
#define __SMSRespCache_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/PDU/PDUSubmitSmResp.h"

#include <list>
////////////////////////////////////////////////////////
class ISMSRespCache{
public:
	typedef list<CH<IOutSMS>> OutSMSlist;
	typedef list<DWORD> SequenceList;
	typedef list<CH<IPDUSubmitSmResp>> RespsList;
	virtual void Initialize(CWnd * w) = 0;

	virtual void AddSMS( CH<IOutSMS> sms ) = 0;
	virtual void AddRESP( SP<IPDUSubmitSmResp> resp ) = 0;
	//�������� ��� �������������� ����������, ��� ���� ������ ��� ������, ��������� �� �������� ���������.
	virtual void FlushAllCacheToFailed() =0;

	virtual CH<IOutSMS> GetSendedSMS () =0;
	//�����, ����� ������ GetFailedSMS, ���������� ������� ���� �� ��������� ������� CommitError ��� UnCommitError
	virtual CH<IOutSMS> GetFailedSMS () =0;

	//Amount of cached *NON-COMPLEATED* (where not all Resps got) SMS
	virtual size_t Size() =0;

	virtual void CommitError() =0;//����������� ������, ���, ������ �� ���� ������������ ����� ���� ���
	virtual void UnCommitError() =0;//�� �����������, ������� �� �� ��������� � �������� ������. �������� ��� ��� ��� ��������. �������� ����������� ��������� ����� �����.
protected:
	virtual void SendMessageCache (int msg) =0;

DECLARE_CH_REFCOUNTING( ISMSRespCache )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////