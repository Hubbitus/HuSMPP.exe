////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : SMS.cpp
// Pavel Alexeev
////////////////////////////////////////////////////////

/*
lOption �� ������ Derdac DLL!!:
0	(00000000): Normal SMS messages
2	(00000010): Delivery notification
4	(00000100): Direct display messages
8	(00001000): 8bit encoded messages
16	(00010000): User Data Header (UDH, logo or ringing tone)
32	(00100000): Virtual SMSC
64	(01000000): Unicode messages
128	(10000000): EMS messages

��� ����������� SMSC -> ESME �������� esm_class ���������� � deliver_sm � data_sm ��������� �������:

����� ��������� (���� 1-0)
x x x x x x x x	�� ����������� - �� ������������ ���� 0 � 1

GSM Network �������������� ������� (bits 7-6)
0 0 x x x x x x	������� ���������
0 1 x x x x x x	UDHI ��������� ����������
1 0 x x x x x x	���������� ���� ������
1 1 x x x x x x	UDHI � ���� ������ ����������
��������� �������� ���������������.
�� ��������� �������� esm_class ���������� � 0x00.
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
	virtual bool isDeliveryReceiptRequested() =0;	/*+79 ������ ������������� �������� �� SMSC*/ \
	virtual bool isDeliveryNotification() =0;	/*������������� ��������, ��������� �� SMSC*/ \
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
	virtual bool isDeliveryReceiptRequested();	/*+79 ������ ������������� �������� �� SMSC*/ \
	virtual bool isDeliveryNotification();	/*������������� ��������, ��������� �� SMSC*/ \
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
	//���� ���������, ������������� ������ �� DerDac (����� ��� ���� �� ��������������)
	enum ContentType {NoOption = 0, DeliveryNotification = 2, DirectDisplay = 4, Bin8bit = 8, UDH = 16, VirtualSMSC = 32, UCS2 = 64, EMS = 128};

	SMS();
	virtual ~SMS(void);

//��� ����� �����
SMS_BASICS_DECLARATION
public:
	//������ ���� � ������ ���������� �����������, ����� ��������� � �������� IPDU, � ������� ���� OptionalParameters!!!
	virtual CH<IPDUOptionalParameters> GetOptionalParameters () =0;
	virtual CH<IPDUOptionalParameter> GetOptionalParameter (WORD paramID) =0;
	virtual std::string GetOptionalParameterStr (WORD paramID) =0;

	//������ ��� �� ���������� ������� ������, � m_pdu ���� IPDU
	//������� ������ ����� ������������ � ����������� ������� ��� :( ����� ��������� � template
	virtual std::string GetShortMessage () {return body;};
	virtual std::string GetShortMessageSQlEscaped () { return strUtils::replaceAll(body, "'", "''");};
	virtual WORD GetDataCoding() =0;
	virtual WORD GetEsmClass() =0;
	virtual long GetlOption();/*��� �������������, ��� � Derdac!*/ \

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