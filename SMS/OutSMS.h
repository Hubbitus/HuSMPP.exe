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

//Таким будем обозначать "отсутствующий" RESP
//Там unsigned, поэтому получается очень большое число просто. Ну и БОГ с ним.
#define NOT_RESP_SEQ -1

////////////////////////////////////////////////////////

class IOutSMS : public SMS {
public:
typedef pair<CH<IPDUSubmitSm>, CH<IPDUSubmitSmResp>> SMSPair; //Пара SMS-RESP
typedef vector<SMSPair> SMSPairVector;

enum splitType { splitSar, splitUDH, splitPayload };

/*96 */
static const int BinMsgLen = 280;
static const int EMSMsgLen = 140;

class Empty{};//Для показа что НЕТУ больше в контейнере, для GetSendedSMS и GetFailedSMS

//	virtual void Initialize (COutcomingRS const & OutRS, bool DoDeliverRoute /*= false*/, int TextMsglen /*=160 чтобы разбить*/, std::string splitType ) =0;
	virtual void Initialize (COutcomingRS const & OutRS, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute /*= false*/, int TextMsglen /*=160 чтобы разбить*/, std::string splitType ) =0;
	virtual void Initialize (CString Sender, CString DestPhone, std::string Body, CTime StartTime, CTime EndTime, boost::shared_ptr<SMSCConfig> SessionConfig, bool DoDeliverRoute = false, CString DeliverRoute  = "", BYTE ContentType = 0, bool CheckDelivery = false, bool DirectDisplay = false,
		int TextMsglen = 160 /* чтобы разбить. Дефолтное значение, если найдется другое по типу - будет оно взято*/,
		std::string splitType = "UDH" /* @TODO: Не знаю какой сделать лчше дефолтным, но какой-то надо, ибо впереде дефолтные */) =0;

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

	//!!!Это контейнер-вектор, потому что будут сплитится автоматом!
	//!!!Приватный, потому что может использоваться только у себя, необходимы блокировки доступа!
	//!!!Самое интересное, что он приватный должен быть только когда IOutSMS уже в контейнере SMSRespCache,
	//!!!Когда используется просто IOutSMS, еще ДО помещения в контейнер SMSRespCache, то ничего плохого нету в прямом доступе.
	//!!!Не знаю как это решить совссем правильно, пока буду учитывать вручную!!!
	virtual SMSPairVector & GetPDUs() =0;

	//Ищет и возвращает первую SMSPair, в которой resp !=0! Тоесть неуспешная отправка
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

	bool m_DoDeliverRoute;	//Вообще надо его или нет
	//Обеспечение RESPов
	//Счетчики
	int CountPDUs;		//Количество всего PDU, на сколько частей разбито
//	int CountResps;		//Количество всего полученных ответов о сабмите
	int CountOkPDUs;	//Количество успешных (resp получен)
	int CountFailPDUs;	//Количество НЕуспешных (resp получен)

	virtual void splitMessage (int length) =0;
/*??
	virtual void splitByUDH(int length) =0;
	virtual void splitBySar(int length) =0;
	virtual void splitByPayload(int length) =0;
*/

	//Ниже подобное SetDataCoding и SetEsmClass, но из lOption, чтобы из базы
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
