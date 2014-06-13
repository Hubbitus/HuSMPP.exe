////////////////////////////////////////////////////////
// Project	: SMPPRouter
// Module	: PDUDeliverSm.h
//
// Modified	: Pavel Alexeev in HuSMPPClient
//	2008-09-02
//	- Method isDeliveryNotification() moved from InSMS
////////////////////////////////////////////////////////

#pragma once

#ifndef __PDUDeliverSm_H__
#define __PDUDeliverSm_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDU.h"
////////////////////////////////////////////////////////
#include <string>
using namespace std;

////////////////////////////////////////////////////////
class IPDUDeliverSm : public IPDU
{
public:
  //
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

  //
  virtual const std::string& GetServiceType() = 0;
  
  virtual BYTE GetSourceAddrTon() = 0;
  virtual BYTE GetSourceAddrNpi() = 0;
  virtual const std::string& GetSourceAddr() = 0;
  
  virtual BYTE GetDestAddrTon() = 0;
  virtual BYTE GetDestAddrNpi() = 0;
  virtual const std::string& GetDestinationAddr() = 0;

  virtual BYTE GetEsmClass() = 0;
  virtual BYTE GetProtocolId() = 0;
  virtual BYTE GetPriorityFlag() = 0;
  virtual const std::string& GetScheduleDeliveryTime() = 0;
  virtual const std::string& GetValidityPeriod() = 0;
  virtual BYTE GetRegisteredDelivery() = 0;
  
  virtual BYTE GetReplaceIfPresentFlag() = 0;
  virtual BYTE GetDataCoding() = 0;
  virtual BYTE GetSmDefaultMsgId() = 0;

  virtual std::string GetShortMessage() = 0;

	virtual bool isDeliveryNotification(){
	//By WireShark: ..00 01.. = Message type  : Short message contains SMSC Delivery Receipt (0x01)
	return ( 
		((GetEsmClass() & 60 /*60=00111100*/) == 4) /*xx0001xx*/
	);
	};

  DECLARE_CH_REFCOUNTING( IPDUDeliverSm )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////