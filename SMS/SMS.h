////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : SMS.cpp
// Pavel Alexeev
////////////////////////////////////////////////////////

/*
lOption ѕќ старой Derdac DLL!!:
0	(00000000): Normal SMS messages
2	(00000010): Delivery notification
4	(00000100): Direct display messages
8	(00001000): 8bit encoded messages
16	(00010000): User Data Header (UDH, logo or ringing tone)
32	(00100000): Virtual SMSC
64	(01000000): Unicode messages
128	(10000000): EMS messages

ƒл€ направлени€ SMSC -> ESME параметр esm_class кодируетс€ в deliver_sm и data_sm следующим образом:

–ежим сообщени€ (биты 1-0)
x x x x x x x x	не примен€етс€ - не используютс€ биты 0 и 1

GSM Network дополнительные функции (bits 7-6)
0 0 x x x x x x	ќбычное сообщение
0 1 x x x x x x	UDHI индикатор установлен
1 0 x x x x x x	”становлен путь ответа
1 1 x x x x x x	UDHI и путь ответа установлен
ќстальные значени€ зарезервированы.
ѕо умолчанию параметр esm_class установлен в 0x00.
*/

#pragma once

#include "../HuSMPPshared.h"
#include "../SMPP/PDU.h"
#include "UDH/UDH.h"
#include "../Utils/lock.h"
#include "../Utils/stringUtils.h"

#include <algorithm>

#define SMS_BASICS_DECLARATION \
public: \
 	virtual bool isNoOption() =0; \
	virtual bool isDeliveryReceiptRequested() =0;	/*+79 запрос подтверждени€ доставки от SMSC*/ \
	virtual bool isDeliveryNotification() =0;	/*ѕодтверждение доставки, пришедшее от SMSC*/ \
	virtual bool isDirectDisplay() =0; /*???*/ \
	virtual bool is8bit() =0; \
	virtual bool isUDH() =0; \
	virtual bool isVirtualSMSC() =0; /*???*/ \
	virtual bool isUCS2() =0; \
	virtual bool isEMS() =0; \
protected: \
	virtual void ParseSMS() =0;

#define SMS_BASICS_DEFINITION \
public: \
 	virtual bool isNoOption(); \
	virtual bool isDeliveryReceiptRequested();	/*+79 запрос подтверждени€ доставки от SMSC*/ \
	virtual bool isDeliveryNotification();	/*ѕодтверждение доставки, пришедшее от SMSC*/ \
	virtual bool isDirectDisplay(){ return false; }; /*???*/ \
	virtual bool is8bit(); \
	virtual bool isUDH(); \
	virtual bool isVirtualSMSC(){ return false; }; /*???*/ \
	virtual bool isUCS2(); \
	virtual bool isEMS(); \
	\
	virtual CH<IIE> GetIE (WORD iei){return m_UDH->GetIE(iei);}; \
protected: \
	virtual void ParseSMS (); \
	int m_lOption;

////////////////////////////////////////////////////////
class SMS{
public:
	//“ипы сообщений, соответствуют старым из DerDac (чтобы всю базу не перемолачивать)
	enum ContentType {NoOption = 0, DeliveryNotification = 2, DirectDisplay = 4, Bin8bit = 8, UDH = 16, VirtualSMSC = 32, UCS2 = 64, EMS = 128};

	SMS();
	virtual ~SMS(void);

//¬с€ маги€ здесь
SMS_BASICS_DECLARATION
public:
	//ƒолжны быть в каждом конкретном реализованы, иначе смотритс€ в корневом IPDU, в котором нету OptionalParameters!!!
	virtual CH<IPDUOptionalParameters> GetOptionalParameters () =0;
	virtual CH<IPDUOptionalParameter> GetOptionalParameter (WORD paramID) =0;
	virtual std::string GetOptionalParameterStr (WORD paramID) =0;

	//потому что не получилось сделать шаблон, а m_pdu типа IPDU
	//поэтому многие будут определ€тьс€ в производных классах уже :( ѕотом разберусь с template
	virtual std::string GetShortMessage () {return body;};
	virtual std::string GetShortMessageSQlEscaped () { return strUtils::replaceAll(body, "'", "''");};
	virtual WORD GetDataCoding() =0;
	virtual WORD GetEsmClass() =0;
	virtual long GetlOption();/*ƒл€ совместимости, как в Derdac!*/ \

	virtual void SetDataCoding (BYTE dcs) =0;
	virtual void SetEsmClass (BYTE esm) =0;

	virtual std::string GetSourceAddr() =0;
	virtual std::string GetDestinationAddr() =0;
	static std::string UCS2toCP1251(std::string input);
	static std::string CP1251toUCS2 (std::string input);
	static long SMS::HexStringToBinInt(std::string S);
	static std::string HexStringToBinString(std::string input);
protected:
	CH<IPDU> m_pdu;
	//+74
	CH<IUDH> m_UDH;
	bool isParsed;
	std::string body;
};