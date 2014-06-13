////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OutSMS.h
// Pavel Alexeev
//
//	@CHANGELOG
//	2008-10-18
//	- Add long m_ID as first parameter of Initialize method with direct fields (not RS)
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

//#include "../HuSMPPshared.h"
#include "SMS.h"
#include "../SMPP/PDU/PDUSubmitSm.h"
#include "../SMPP/PDU/PDUSubmitSmResp.h"
#include "../OutcomingRS.h"
#include "../HuSMSCConfig.h"

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

////////////////////////////////////////////////////////

//����� ����� ���������� "�������������" RESP
//��� unsigned, ������� ���������� ����� ������� ����� ������. �� � ��� � ���.
#define NOT_RESP_SEQ -1

////////////////////////////////////////////////////////

class IOutSMS : public SMS {
public:
typedef pair<CH<IPDUSubmitSm>, CH<IPDUSubmitSmResp>> SMSPair; //���� SMS-RESP
typedef vector<SMSPair> SMSPairVector;

enum splitType { splitSar, splitUDH, splitPayload };

/*96 */
static const int BinMsgLen = 280;
static const int EMSMsgLen = 140;

class Empty{};//��� ������ ��� ���� ������ � ����������, ��� GetSendedSMS � GetFailedSMS

//	virtual void Initialize (COutcomingRS const & OutRS, bool DoDeliverRoute /*= false*/, int TextMsglen /*=160 ����� �������*/, std::string splitType ) =0;
	virtual void Initialize (COutcomingRS const & OutRS, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute /*= false*/, int TextMsglen /*=160 ����� �������*/, std::string splitType ) =0;
	virtual void Initialize (CString Sender, CString DestPhone, std::string Body, CTime StartTime, CTime EndTime, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute = false, CString DeliverRoute  = "", BYTE ContentType = 0, bool CheckDelivery = false, bool DirectDisplay = false,
		int TextMsglen = 160 /* ����� �������. ��������� ��������, ���� �������� ������ �� ���� - ����� ��� �����*/,
		std::string splitType = "UDH" /* @TODO: �� ���� ����� ������� ���� ���������, �� �����-�� ����, ��� ������� ��������� */) =0;

SMS_BASICS_DECLARATION
public:
	virtual bool isUserAcknowledgment() =0;

	virtual CH<IPDUOptionalParameters> GetOptionalParameters (){return m_pdu->GetOptionalParameters();};
	virtual CH<IPDUOptionalParameter> GetOptionalParameter (WORD paramID) {return GetOptionalParameters()->GetParameter(paramID);};
	virtual std::string GetOptionalParameterStr (WORD paramID) =0;

//	virtual CString GetShortMessage ();
//	virtual CString GetShortMessageSQlEscaped ();

	virtual std::string GetSourceAddr() {chASSERT ( isParsed ); return m_pdu->GetSourceAddr();};
	virtual std::string GetDestinationAddr() {chASSERT ( isParsed ); return m_pdu->GetDestinationAddr();};

	virtual WORD GetDataCoding() {chASSERT ( isParsed ); return m_pdu->GetDataCoding();};
	virtual WORD GetEsmClass() {chASSERT ( isParsed ); return m_pdu->GetEsmClass();};

	virtual void SetDataCoding (BYTE dcs){chASSERT ( isParsed ); m_pdu->SetDataCoding(dcs);};
	virtual void SetEsmClass (BYTE esm){chASSERT ( isParsed ); m_pdu->SetEsmClass(esm);};

	//!!!��� ���������-������, ������ ��� ����� ��������� ���������!
	//!!!���������, ������ ��� ����� �������������� ������ � ����, ���������� ���������� �������!
	//!!!����� ����������, ��� �� ��������� ������ ���� ������ ����� IOutSMS ��� � ���������� SMSRespCache,
	//!!!����� ������������ ������ IOutSMS, ��� �� ��������� � ��������� SMSRespCache, �� ������ ������� ���� � ������ �������.
	//!!!�� ���� ��� ��� ������ ������� ���������, ���� ���� ��������� �������!!!
	virtual SMSPairVector & GetPDUs() =0;

	//���� � ���������� ������ SMSPair, � ������� resp !=0! ������ ���������� ��������
//	virtual SMSPair & GetFirstFailedSMS ();
protected:
	CH<IPDUSubmitSm> m_pdu;
	SMSPairVector m_PartsPDUs;
	int m_TextMsglen;

	bool	m_CheckDelivery;
	CString	m_DestPhone;
	bool	m_DirectDisplay;
	CTime	m_EndTime;
	long	m_ID;
	long	m_JobStatus;
	long	m_LastError;
	CString	m_Sender;
	CTime	m_SentTime;
	CTime	m_StartTime;
	BYTE	m_AttDone;
	BYTE	m_ContentType;
	CString	m_SmscMsgID;
	CString m_DeliverRoute;

	bool m_DoDeliverRoute;	//������ ���� ��� ��� ���
	//����������� RESP��
	//��������
	int CountPDUs;		//���������� ����� PDU, �� ������� ������ �������
//	int CountResps;		//���������� ����� ���������� ������� � �������
	int CountOkPDUs;	//���������� �������� (resp �������)
	int CountFailPDUs;	//���������� ���������� (resp �������)

	virtual void splitMessage (int length) =0;
/*??
	virtual void splitByUDH(int length) =0;
	virtual void splitBySar(int length) =0;
	virtual void splitByPayload(int length) =0;
*/

	//���� �������� SetDataCoding � SetEsmClass, �� �� lOption, ����� �� ����
	virtual void ParseSetDataCoding (int intOption) =0;
	virtual void ParseSetEsmClass (int intOption) =0;

public:
	virtual bool AddRESP( CH<IPDUSubmitSmResp> resp ) =0;

	virtual void MarkBad( DWORD status = ESME_FLUSHERR ) =0;

	virtual bool RespComplete (){ chASSERT ( isParsed ); return ( (CountOkPDUs + CountFailPDUs) == CountPDUs); };
	virtual int getCountPDUs (){ chASSERT ( isParsed ); return CountPDUs; };
	virtual int getCountOkPDUs (){ chASSERT ( isParsed ); return CountOkPDUs; };
	virtual int getCountFailPDUs (){ chASSERT ( isParsed ); return CountFailPDUs; };

	long GetDB_ID () { return m_ID; };

	DECLARE_CH_REFCOUNTING( IOutSMS )
};
