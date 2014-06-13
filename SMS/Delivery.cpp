////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: Delivery.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-28 15:04
//
//	2008-09-03
//	- In GetDlvrMessageState() in case absent OPTMessageState inicialisation chhnged from:
//		retVal->Initialize((OPTMessageState::REALTYPE)-1);
//		to
//		retVal->Initialize(OPTMessageState::UNDEFINED);
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Delivery.h"

//////////////////////////////////////////////////////////////////

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

//////////////////////////////////////////////////////////////////

Delivery::Delivery(CH<IPDUDeliverSm> pdu, std::string deliveryFormat)
	:InSMS (pdu)
	,m_strDeliveryFormat (deliveryFormat){
parseDelivery();
}

//////////////////////////////////////////////////////////////////
CH<OPTSourceSubaddress>
Delivery::GetDlvrSourceSubaddress(){
ASSERT(isDeliveryNotification());

CH<OPTSourceSubaddress> retVal;

CH<IPDUOptionalParameter> optP = GetOptionalParameter(PDU_OPT_SourceSubaddress);

	if (PDU_OPT_UNKNOWN == optP->GetTagId()){//empty initialize
	retVal->Initialize("");
	}
	else{
	retVal = SafeDynamicCastCH<OPTSourceSubaddress, IPDUOptionalParameter>( optP );
	}

return retVal;
}

//////////////////////////////////////////////////////////////////
CH<OPTReceiptedMessageId>
Delivery::GetDlvrReceiptedMessageId(){
ASSERT(isDeliveryNotification());

CH<OPTReceiptedMessageId> retVal;

CH<IPDUOptionalParameter> optP = GetOptionalParameter(PDU_OPT_ReceiptedMessageId);

	if (PDU_OPT_UNKNOWN == optP->GetTagId()){//empty initialize
	retVal->Initialize("");
	}
	else{
	retVal = SafeDynamicCastCH<OPTReceiptedMessageId, IPDUOptionalParameter>( optP );
	}

return retVal;
}

//////////////////////////////////////////////////////////////////
CH<OPTMessageState>
Delivery::GetDlvrMessageState(){
ASSERT(isDeliveryNotification());

CH<OPTMessageState> retVal;

CH<IPDUOptionalParameter> optP = GetOptionalParameter(PDU_OPT_MessageState);

	if (PDU_OPT_UNKNOWN == optP->GetTagId()){//empty initialize
	retVal->Initialize(OPTMessageState::UNDEFINED);
	}
	else{
	retVal = SafeDynamicCastCH<OPTMessageState, IPDUOptionalParameter>( optP );
	}
return retVal;
}

//////////////////////////////////////////////////////////////////
CH<OPTNetworkErrorCode>
Delivery::GetDlvrNetworkErrorCode(){
ASSERT(isDeliveryNotification());

CH<OPTNetworkErrorCode> retVal;

CH<IPDUOptionalParameter> optP = GetOptionalParameter(PDU_OPT_NetworkErrorCode);

	if (PDU_OPT_UNKNOWN == optP->GetTagId()){//empty initialize
	retVal->Initialize((OPTNetworkErrorCode::REALTYPE)OPTNetworkErrorCode::UNDEFINED);
	}
	else{
	retVal = SafeDynamicCastCH<OPTNetworkErrorCode, IPDUOptionalParameter>( optP );
	}

return retVal;
}

//////////////////////////////////////////////////////////////////
void
Delivery::parseDelivery(){
ASSERT(isDeliveryNotification());

	if (!body.empty() && m_strDeliveryFormat != "opt"){//Let the Text-representation has more priority
	boost::regex expression;
	boost::smatch m;
		if (!m_strDeliveryFormat.empty()){
		expression.assign(m_strDeliveryFormat, boost::regex::perl);
		}
		else{//Defaults
		expression.assign("id:(\\d{10}) sub:(\\d{3}) dlvrd:(\\d{3}) submit date:(\\d{10}) done date:(\\d{10}) stat:(DELIVERED|DELIVRD|EXPIRED|DELETED|UNDELIVERABLE|ACCEPTED|UNKNOWN|REJECTED) err:(\\d{3}) text:(.{0,20})", boost::regex::perl);
		}

		if(regex_match(body, m, expression)){
		m_strID			= m[1];
		m_strSub		= m[2];
		m_strDlvrd		= m[3];
		m_strSubmitDate	= m[4];
		m_strDoneDate	= m[5];
		m_chStat->Initialize(m[6]);//Initialize from string name
		m_strErr		= m[7];
		m_strText		= m[8];
		}
		else{
		inSMSLog += "Delivery format is incorrect! Delivery not parsed!";
		throw new DeliveryFormatError("Delivery format is incorrect! Delivery not parsed! DeliveryText: " + body);
		}
	}
	else{//Optional parameters only
	m_strID			= GetDlvrReceiptedMessageId()->GetRealValue();
//	m_strSub		= "";
//	m_strDlvrd		= "";
//	m_strSubmitDate	= "";
//	m_strDoneDate	= "";
	m_chStat		= GetDlvrMessageState();
//-	m_strErr		= boost::lexical_cast<std::string>(GetDlvrNetworkErrorCode()->GetErrorCode());
	// We want -1 ensted of 65535
	m_strErr		= boost::lexical_cast<std::string>(
		( GetDlvrNetworkErrorCode()->GetErrorCode() == OPTNetworkErrorCode::UNDEFINED ? -1 : GetDlvrNetworkErrorCode()->GetErrorCode() )
	);
//	m_strText		= "";

	m_strSubAddress	= GetSubAddress();
	}
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetID() const{
return m_strID;
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetSub() const{
return m_strSub;
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetDlvrd() const{
return m_strDlvrd;
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetSubmitDate() const{
return m_strSubmitDate;	
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetDoneDate() const{
return m_strDoneDate;
}

//////////////////////////////////////////////////////////////////
CH<OPTMessageState>
Delivery::GetStat() const{
return m_chStat;
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetErr() const{
return m_strErr;
}

//////////////////////////////////////////////////////////////////
const std::string&
Delivery::GetText() const{
return m_strText;
}

//////////////////////////////////////////////////////////////////
std::string
Delivery::GetSubAddress(){
return GetDlvrSourceSubaddress()->GetSubaddress();
}