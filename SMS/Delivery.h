////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: Delivery.h
// Author	: Pavel Alexeev
// Created	: 2008-08-28 15:04
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "InSMS.h"
#include "Utils/errors.h"

////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////

class DeliveryFormatError : public CError{ //For exceptions
public:
	DeliveryFormatError (const std::string& err = "") : CError(err){};
};

////////////////////////////////////////////////////////
class Delivery : public InSMS {
public:
	Delivery(CH<IPDUDeliverSm> pdu, std::string deliveryFormat);

	void parseDelivery();

	virtual const std::string& GetID() const;
	virtual const std::string& GetSub() const;
	virtual const std::string& GetDlvrd() const;
	virtual const std::string& GetSubmitDate() const;
	virtual const std::string& GetDoneDate() const;
	virtual CH<OPTMessageState> GetStat() const;
	virtual const std::string& GetErr() const;
	virtual const std::string& GetText() const;

	//Телефон, кому доставляли
	virtual std::string GetSubAddress();
private:
	std::string m_strDeliveryFormat;

	std::string m_strID;
	std::string m_strSub;
	std::string m_strDlvrd;
	std::string m_strSubmitDate;
	std::string m_strDoneDate;
	CH<OPTMessageState> m_chStat;
	std::string m_strErr;
	std::string m_strText;

	std::string m_strSubAddress;

	virtual CH<OPTSourceSubaddress> GetDlvrSourceSubaddress();
	virtual CH<OPTReceiptedMessageId> GetDlvrReceiptedMessageId();
	virtual CH<OPTMessageState> GetDlvrMessageState();
	virtual CH<OPTNetworkErrorCode> GetDlvrNetworkErrorCode();
};