////////////////////////////////////////////////////////
// Project	: SMPPSample
// Module	: OutSMS.cpp
// Author	: Pavel Alexeev
//
// CHNGELOG
//	2008-10-17
//	Reimplement OutSMSImpl::Initialize(COutcomingRS const & OutRS, bool DoDeliverRoute = false, int TextMsglen = 160, std::string splitType ){
//	Throught main: void OutSMSImpl::Initialize(CString Sender, CString DestPhone, std::string Body, CTime StartTime, CTime EndTime, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute /*= false*/, CString DeliverRoute /*= ""*/, BYTE ContentType /*= 0*/, bool CheckDelivery /*= false*/, bool DirectDisplay /*= false*/, int TextMsglen /*= 160*/ /*����� �������. ��������� ��������, ���� �������� ������ �� ���� - ����� ��� �����*/ , std::string splitType )
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutSMS.h"

#include "../HuSMSCConfig.h"

#include "../Common/Singles/singleton.h" //��� ����� ����

/////////////////////////////////////////////////////////////
//Both for random generation
#include <boost/random.hpp>
#include <boost/thread/xtime.hpp>

/////////////////////////////////////////////////////////////

class SMSsplitUDHParam{
public:
	WORD SingleSMSLength;
	WORD MultipleSMSLength;
	WORD Multiplier;

	SMSsplitUDHParam(
		WORD _SingleSMSLength,
		WORD _MultipleSMSLength,
		WORD _Multiplier)
		: SingleSMSLength(_SingleSMSLength)
		, MultipleSMSLength(_MultipleSMSLength)
		, Multiplier(_Multiplier)
	{
	}
};//c SMSsplitParam

/////////////////////////////////////////////////////////////

class SMSsplitUDHParams{
	typedef std::map<WORD, boost::shared_ptr<SMSsplitUDHParam> > SMSsplitUDHParams_map;
	enum SMSTypes { BIT7 = 0, UCS2 = 64 };

public:
	SMSsplitUDHParams(){
	//Inicialization of known types:
	map_[0 ]	= boost::shared_ptr<SMSsplitUDHParam>(new SMSsplitUDHParam(140, 128, 1));
	map_[64]	= boost::shared_ptr<SMSsplitUDHParam>(new SMSsplitUDHParam(70, 67, 2));
	}

	boost::shared_ptr<SMSsplitUDHParam> operator[](WORD ind){ return map_[ind]; }
private:
	SMSsplitUDHParams_map map_;
};//c SMSsplitUDHParams

/////////////////////////////////////////////////////////////

class OutSMSImpl : public IOutSMS {
public:
  OutSMSImpl();

//	void Initialize (COutcomingRS const & OutRS, bool DoDeliverRoute /*= false*/, int TextMsglen /*=160 ����� �������*/, std::string splitType );
	void Initialize (COutcomingRS const & OutRS, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute /*= false*/, int TextMsglen = 160, std::string splitType = "UDH");
	void Initialize (CString Sender, CString DestPhone, std::string Body, CTime StartTime, CTime EndTime, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute = false, CString DeliverRoute = "", BYTE ContentType = 0, bool CheckDelivery = false, bool DirectDisplay = false,
		int TextMsglen = 160/*����� �������. ��������� ��������, ���� �������� ������ �� ���� - ����� ��� �����*/, std::string splitType = "UDH" );


	virtual bool AddRESP( CH<IPDUSubmitSmResp> resp );

	std::string GetOptionalParameterStr (WORD paramID);

	//����� � 0��� ���� ������ ������ ESME_FLUSHERR �����������
	virtual void MarkBad( DWORD status ) { m_PartsPDUs.front().second->SetResultCode(status); }

	virtual bool isUserAcknowledgment();

	//!!!��� ���������-������, ������ ��� ����� ��������� ���������!
	//!!!���������, ������ ��� ����� �������������� ������ � ����, ���������� ���������� �������!
	//!!!����� ����������, ��� �� ��������� ������ ���� ������ ����� IOutSMS ��� � ���������� SMSRespCache,
	//!!!����� ������������ ������ IOutSMS, ��� �� ��������� � ��������� SMSRespCache, �� ������ ������� ���� � ������ �������.
	//!!!�� ���� ��� ��� ������ ������ ���������, ���� ���� ��������� �������!!!
	virtual SMSPairVector & GetPDUs();

SMS_BASICS_DEFINITION

protected:
	virtual void splitMessage (int length);
	virtual void splitByUDH();
//??	virtual void splitBySar(int length);
//??	virtual void splitByPayload(int length);

	virtual void ParseSetDataCoding (int intOption);
	virtual void ParseSetEsmClass (int intOption);
private:
	CLock m_Lock;
	std::string splitType_;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOutSMS, OutSMSImpl )

////////////////////////////////////////////////////////
//��������� �����������. ����� ������ ������ ������������, �� ������ ��� ����������
//��� ������������� ����� �������������
OutSMSImpl::OutSMSImpl(){
isParsed = false;
m_lOption = 0;
m_PartsPDUs.clear();
CountPDUs = /*CountResps =*/ CountOkPDUs = CountFailPDUs = 0;
m_DoDeliverRoute = false;
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::Initialize(COutcomingRS const & OutRS, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute = false, int TextMsglen, std::string splitType ){
CLocalLock lock (m_Lock);
Initialize(
	OutRS.m_Sender,
	OutRS.m_DestPhone,
	std::string(OutRS.m_Body),
	OutRS.m_StartTime,
	OutRS.m_EndTime,
	SessionConfig,
	DoDeliverRoute,
	OutRS.m_DeliverRoute,
	OutRS.m_ContentType,
	(bool)OutRS.m_CheckDelivery,
	(bool)OutRS.m_DirectDisplay,
	TextMsglen,
	splitType
	);

//This is additional from BD need
m_ID = OutRS.m_ID;

/* It is not used for send fields of recordset
#pragma warning(push)
#pragma warning(disable:4800)
m_ID			= OutRS.m_ID;
m_JobStatus		= OutRS.m_JobStatus;
m_LastError		= OutRS.m_LastError;
m_SentTime		= OutRS.m_SentTime;
m_AttDone		= OutRS.m_AttDone;
m_SmscMsgID		= OutRS.m_SmscMsgID;
#pragma warning(pop)
*/
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::Initialize(
	CString Sender,
	CString DestPhone,
	std::string Body,
	CTime StartTime,
	CTime EndTime,
	boost::shared_ptr<SMSCConfig> SessionConfig,
	bool DoDeliverRoute /*= false*/,
	CString DeliverRoute /*= ""*/,
	BYTE ContentType /*= 0*/,
	bool CheckDelivery /*= false*/,
	bool DirectDisplay /*= false*/,
	int TextMsglen /*= 160*/ /*����� �������. ��������� ��������, ���� �������� ������ �� ���� - ����� ��� �����*/
	, std::string splitType
	){
CLocalLock lock (m_Lock);

CountPDUs = /*CountResps =*/ CountOkPDUs = CountFailPDUs = 0;

m_Sender = Sender;
m_CheckDelivery = CheckDelivery;
m_DestPhone = DestPhone;
m_DirectDisplay = DirectDisplay;

m_StartTime = StartTime;
m_EndTime = EndTime;

m_ContentType = ContentType;
m_DoDeliverRoute = DoDeliverRoute;
m_DeliverRoute = DeliverRoute;

m_TextMsglen = TextMsglen;
m_lOption = ContentType;

//-65 body = Body;
	if (m_lOption == 1){
	body = SMS::CP1251toUCS2(std::string(Body));
	m_lOption = 64;
	}
	else body = Body;

	if (SessionConfig){
	//��������������, "�����������" �������������
	m_pdu->SetDestAddrNpi(SessionConfig->getDestNPI());
	m_pdu->SetDestAddrTon(SessionConfig->getDestTON());
	m_pdu->SetSourceAddrTon(SessionConfig->getSrcTON());
	m_pdu->SetSourceAddrNpi(SessionConfig->getDestNPI());
	}

isParsed = true;//������� �������, �� ���� �����.
ParseSMS();
}

/*
//////////////////////////////////////////////////////////////////
void
OutSMSImpl::Initialize(COutcomingRS const & OutRS, bool DoDeliverRoute, int TextMsglen, boost::shared_ptr<SMSCConfig> SessionConfig, std::string splitType ){
CLocalLock lock (m_Lock);

//��������������, "�����������" �������������
m_pdu->SetDestAddrNpi(SessionConfig->getDestNPI());
m_pdu->SetDestAddrTon(SessionConfig->getDestTON());
m_pdu->SetSourceAddrTon(SessionConfig->getSrcTON());
m_pdu->SetSourceAddrNpi(SessionConfig->getDestNPI());
	
//����������� �������������
Initialize (OutRS, DoDeliverRoute, TextMsglen, splitType);
}
*/

//////////////////////////////////////////////////////////////////
void OutSMSImpl::ParseSMS(){
CLocalLock lock (m_Lock);

m_pdu->SetDestinationAddr(m_DestPhone);
m_pdu->SetSourceAddr(m_Sender);

m_pdu->SetRegisteredDelivery(m_CheckDelivery);

ParseSetDataCoding (m_lOption);
ParseSetEsmClass (m_lOption);

	if (m_DoDeliverRoute){
	CH<OPTDeliverRoute> dRoute;
	dRoute->Initialize(std::string(m_DeliverRoute.GetString()));
	m_pdu->GetOptionalParameters()->SetParameter(SafeCastCH<IPDUOptionalParameter, OPTDeliverRoute>(dRoute));
	}

	if (isEMS()){//�������� ������ ���� ������, ��� ��� ������������� � ��������� ������!
	body = HexStringToBinString(body);
	splitMessage(EMSMsgLen);
	}
	else if (isUCS2()){
	//-65 ����� ����������� ���������� ������� ��� � �� �������������� �� ������!
//??	body = "00" + body;
	body = HexStringToBinString(body);
	splitMessage(BinMsgLen);
//??	m_pdu->SetEsmClass(m_pdu->GetEsmClass() | 64); //Set UDH
	}
	else if (isUDH() || is8bit()){
	splitMessage(BinMsgLen);
	}
	else{//����� ���������� ��� ����
	splitMessage(m_TextMsglen);
	}
isParsed = true;
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isNoOption(){
chASSERT ( isParsed );
return (
	(m_pdu->GetDataCoding() & 252 /*11111100*/) == 252
);//���� 7-2 ���� �������
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isDeliveryReceiptRequested(){
chASSERT ( isParsed );
return (m_pdu->GetRegisteredDelivery() != 0);
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isDeliveryNotification(){
return ( 
	((m_pdu->GetEsmClass() & 60 /*60=00111100*/) == 8) /*xx0010xx*/
);
}

//////////////////////////////////////////////////////////////////
bool	//������ ������������� ��������, ��� �������� �� SMSC
OutSMSImpl::isUserAcknowledgment(){
chASSERT ( isParsed );
return (
//-79		(m_pdu->GetEsmClass() & 0x10) == 0x10 /*00010000*/
	(m_pdu->GetEsmClass() & 0x08) == 0x08 /*00001000*/
	);
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::is8bit(){
chASSERT ( isParsed );
CLocalLock lock (m_Lock);

BYTE dcs = m_pdu->GetDataCoding();
return ( 
	( (!((dcs & 192) == 192)) && ((dcs & 4) == 4) ) /*11000000, 00000100 ���� ������� 2 ����, � 3� - 1*/
	||
	((dcs & 244) == 244) /*11110100*/
);
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isUDH(){
chASSERT ( isParsed );

return (
	(m_pdu->GetEsmClass() & 64 /*64=01000000*/) == 64
);
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isUCS2(){
chASSERT ( isParsed );
CLocalLock lock (m_Lock);
BYTE dcs = m_pdu->GetDataCoding();
return ( 
	( ((dcs & 192) == 0) && ((dcs & 8) == 8) ) /*11000000, 00001000 ���� ������� 2 ����, � 3� - 1*/
	||
	((dcs & 224) == 224) /*11100000*/
);
}

//////////////////////////////////////////////////////////////////
bool
OutSMSImpl::isEMS(){
chASSERT ( isParsed );
//�������� �� lOption, ������ ��� ���, ������, �����-�� ������������ ����������, ��� �������������
return ((m_lOption & EMS) == EMS);
}

//////////////////////////////////////////////////////////////////
OutSMSImpl::SMSPairVector &
OutSMSImpl::GetPDUs(){
chASSERT ( isParsed );
	return m_PartsPDUs;
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::splitMessage(int length){
//�� �� ����� ���������� ��������
CLocalLock lock (m_Lock);

m_PartsPDUs.clear();

//������ ������� ����� ���������� �����, ������� ������ body!
CountPDUs = (int)((body.length() % length)?(body.length() / length + 1):(body.length() / length));
/* ��������� ����� � �����, ��� �.�. ������������!
CH<IPDUSubmitSmResp> defResp;
defResp->SetSequenceNumber((DWORD)NOT_RESP_SEQ);
*/
	for(int i = 0; i < CountPDUs; i++){
	CH<IPDUSubmitSmResp> defResp;
	defResp->SetSequenceNumber((DWORD)NOT_RESP_SEQ);

	//��� ���� ���� *����������*
	CH<IPDUSubmitSm> tmpPDU;
	//������������� �������� ������ ����� ��������� �������������
	tmpPDU->Initialize(m_pdu->GetRawData(), m_pdu->GetInSocket());
	tmpPDU->SetShortMessage(body.substr(i*length, length));
	m_PartsPDUs.push_back(make_pair(tmpPDU, defResp));
	}
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::ParseSetDataCoding(int intOption){
CLocalLock lock (m_Lock);
	if(intOption == 0){
	m_pdu->SetDataCoding((BYTE)0);
	return;
	}

BYTE dcs = 0;
#pragma chMSG("Fix it later, for FULL data coding support")
/*
	if (	((intOption & Bin8bit) == Bin8bit)
			||
			((intOption & UDH) == UDH)
		)
	dcs |= 0x04;  /*00000100 */


	if ( (intOption & UCS2) == UCS2 )
	dcs |= 0x08;  /*00001000 */

m_pdu->SetDataCoding(dcs);
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::ParseSetEsmClass(int intOption){
CLocalLock lock (m_Lock);

BYTE esm = 0;
	//.... ..01 = Delivery receipt  : Delivery receipt requested (for success or failure) (0x01)
//-79	if (CheckDelivery) esm |= 0x01; /*00000001*/

	if(intOption < 1){
	return m_pdu->SetEsmClass(esm); // do not do Sisif work
	}

#pragma chMSG("Fix it later, for FULL esm_class support")

//�������� 0 � 1 ���� - ����� SMSC �� ��������� (Store and Forward)
//�� ����, � ��� � 0 �� ������!
//	esm &= ~ 0x03;

//65??	if ( (intOption & DirectDisplay) == DirectDisplay )
//65??	esm |=  /*0000 */

	if (
		((intOption & Bin8bit) == Bin8bit)
		||
		((intOption & UDH) == UDH)
		||
		((intOption & EMS) == EMS)
		)
	esm |= 0x40;  /*01000000 */

m_pdu->SetEsmClass(esm);
}

//////////////////////////////////////////////////////////////////
/*
  ������ ��������� � ������ ��� ����-�����, ��� ���� ������ ���������� true ���� ���������,
  ��� false ���� ����������� resp �� ��� ���� �����
*/
bool
OutSMSImpl::AddRESP( CH<IPDUSubmitSmResp> resp ){
chASSERT ( isParsed );
CLocalLock lock (m_Lock);

//��������, ���������� ���� �� ����� ���������� ���, ������ ��� ����� ������������ ���������� ����
OutSMSImpl::SMSPairVector::iterator pairPDUsIter = GetPDUs().begin();
			//������ ��� ����� ���� ��������� �� ��������� ������, �� ��� ������� 1 ����� ��������
	while (
		   (pairPDUsIter != GetPDUs().end())
		   &&
		   ( pairPDUsIter->first->GetSequenceNumber() != resp->GetSequenceNumber() )  
		   ){
	++pairPDUsIter;
	}
		
	if ( pairPDUsIter != GetPDUs().end() && pairPDUsIter->first->GetSequenceNumber() == resp->GetSequenceNumber() ){
	//������ �����, ���������, � ���������� ������
	pairPDUsIter->second = resp;
//	CountResps++;
		if (resp->GetHeader().command_status == 0) CountOkPDUs++;
		else CountFailPDUs++;
	return true;
	}
	else return false;//������ �� ��� ���� ��� ����
}

//////////////////////////////////////////////////////////////////
std::string
OutSMSImpl::GetOptionalParameterStr(WORD paramID){
return ((m_pdu->GetOptionalParameters()->GetParameter(paramID))->operator std::string());
}

//////////////////////////////////////////////////////////////////
void
OutSMSImpl::splitByUDH(){
CLocalLock lock (m_Lock);

m_PartsPDUs.clear();

static const SMSsplitUDHParams splitParams;
const boost::shared_ptr<SMSsplitUDHParam> splitParam = splitParams[ isUCS2 ? UCS2 : BIT7 ];

	if (body.length() > splitParam->SingleSMSLength){
	//������ ������� ����� ���������� �����, ������� ������ body!
	CountPDUs = (int)((body.length() % splitParam->MultipleSMSLength) ? (body.length() / splitParam->MultipleSMSLength + 1):(body.length() / splitParam->MultipleSMSLength));

	static boost::mt19937 rng;	// produces randomness out of thin air
						// see pseudo-random number generators
	static rng.seed( boost::get_xtime( boost::get_system_time() ).nsec );
	static boost::uniform_int<> six(1,255);	// distribution that maps to 1..255
										// see random number distributions
	static boost::variate_generator< boost::mt19937&, boost::uniform_int<> > gen(rng, six);

	BYTE referenceID = gen();

		for(int i = 0; i < CountPDUs; i++){
		CH<IPDUSubmitSmResp> defResp;
		defResp->SetSequenceNumber((DWORD)NOT_RESP_SEQ);

		//��� ���� ���� *����������*
		CH<IPDUSubmitSm> tmpPDU;
		//������������� �������� ������ ����� ��������� �������������
		tmpPDU->Initialize(m_pdu->GetRawData(), m_pdu->GetInSocket());
		tmpPDU->SetShortMessage(body.substr(i*length, length));
		m_PartsPDUs.push_back(make_pair(tmpPDU, defResp));
		}
	}
}