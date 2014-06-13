////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSm.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-16 - //91
//		Return-type of method GetShortMessage() changed from "std::string" to "const std::string&"
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"

#include "../PDU.h"

////////////////////////////////////////////////////////

class IPDUSubmitSm : public IPDU{
public:
	virtual void SetServiceType( const char* service_type ) = 0;

	virtual void SetSourceAddrTon( BYTE source_addr_ton ) = 0;
	virtual void SetSourceAddrNpi( BYTE source_addr_npi ) = 0;
	virtual void SetSourceAddr( const char* source_addr ) = 0;

	virtual void SetDestAddrTon( BYTE dest_addr_ton ) = 0;
	virtual void SetDestAddrNpi( BYTE dest_addr_npi ) = 0;
	virtual void SetDestinationAddr( const char* destination_addr ) = 0;

	virtual void SetEsmClass( BYTE esm_class ) = 0;
	virtual void SetProtocolId( BYTE protocol_id ) = 0;
	virtual void SetPriorityFlag( BYTE priority_flag ) = 0;
	virtual void SetScheduleDeliveryTime( const char* schedule_delivery_time ) = 0;
	virtual void SetValidityPeriod( const char* validity_period ) = 0;
	virtual void SetRegisteredDelivery( BYTE registered_delivery ) = 0;

	virtual void SetReplaceIfPresentFlag( BYTE replace_if_present_flag ) = 0;
	virtual void SetDataCoding( BYTE data_coding ) = 0;
	virtual void SetSmDefaultMsgId( BYTE sm_default_msg_id ) = 0;

	virtual void SetShortMessage( const char* short_message ) = 0;
	//-71
	virtual void SetShortMessage( const std::string short_message ) = 0;
					   
	virtual const std::string& GetServiceType() = 0;

	virtual BYTE GetSourceAddrTon() = 0;
	virtual BYTE GetSourceAddrNpi() = 0;
	virtual const std::string& GetSourceAddr() = 0;

	virtual BYTE GetDestAddrTon() = 0;
	virtual BYTE GetDestAddrNpi() = 0;
	virtual const string& GetDestinationAddr() = 0;

	virtual BYTE GetEsmClass() = 0;
	virtual BYTE GetProtocolId() = 0;
	virtual BYTE GetPriorityFlag() = 0;
	virtual const std::string& GetScheduleDeliveryTime() = 0;
	virtual const std::string& GetValidityPeriod() = 0;
	virtual BYTE GetRegisteredDelivery() = 0;

	virtual BYTE GetReplaceIfPresentFlag() = 0;
	virtual BYTE GetDataCoding() = 0;
	virtual BYTE GetSmDefaultMsgId() = 0;

	virtual const std::string GetShortMessage() = 0;

DECLARE_CH_REFCOUNTING( IPDUSubmitSm )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////