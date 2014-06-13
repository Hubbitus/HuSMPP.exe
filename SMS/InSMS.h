////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : InSMS.h
// Pavel Alexeev
// Rewritten in HuSMPP by Pavel Alexeev 2008-07-30
//	2008-07-30
//	- Replace CString to std::string in inSMSLog property and appropriate methods
//
//	2008-08-28
//	- Move Delivery - related methods into separate Delivery class
//	- Steep from CH<> template-model to using boost::shared_ptr.
//		So, we can now use normal inheritance without hacks, tricks and restrictions!
//
//	2008-09-02
//	- Method realisatiion isDeliveryNotification() moved to PDUDeliverSm
//	- Method
//	 virtual void Initialize (CH<IPDUDeliverSm> pdu) =0;
//	 removed as legacy.
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "sms.h"
#include "../HuSMPPshared.h"
#include "../SMPP/PDU/PDUDeliverSm.h"

#include <string>

////////////////////////////////////////////////////////

class InSMS : public SMS {
public:
//Definition but not Declaration by design issue and moving from CH<> tamplate
SMS_BASICS_DEFINITION
public:
	InSMS(CH<IPDUDeliverSm> pdu);

	virtual std::string GetLog(){ return inSMSLog; };

	virtual CH<IPDUOptionalParameters> GetOptionalParameters () { return m_pdu->GetOptionalParameters(); };
	virtual CH<IPDUOptionalParameter> GetOptionalParameter (WORD paramID) { return GetOptionalParameters()->GetParameter(paramID); };
	virtual std::string GetOptionalParameterStr ( WORD paramID ) { return ((m_pdu->GetOptionalParameters()->GetParameter(paramID))->operator std::string()); };

	virtual std::string GetSourceAddr() { return m_pdu->GetSourceAddr(); };
	virtual std::string GetDestinationAddr() { return m_pdu->GetDestinationAddr(); };

	virtual WORD GetDataCoding() { return m_pdu->GetDataCoding(); };
	virtual WORD GetEsmClass() { return m_pdu->GetEsmClass(); };
	virtual void SetDataCoding (BYTE dcs){ m_pdu->SetDataCoding(dcs); };
	virtual void SetEsmClass (BYTE esm){ m_pdu->SetEsmClass(esm); };

	WORD GetMsgLinkID (){ return msgPartLinkID; };
	WORD GetMsgPartNo (){ return msgPartNo; };
	WORD GetMsgPartsTotal (){ return msgPartsTotal; };
protected:
	std::string inSMSLog;
	CH<IPDUDeliverSm> m_pdu;

	void parseUDH();
	//-69
	WORD msgPartLinkID;
	WORD msgPartNo;
	WORD msgPartsTotal;
};