////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindTransmitter.h
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
////////////////////////////////////////////////////////

#pragma once
////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDU.h"
#include <string>
////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////
class IPDUBindTransmitter : public IPDU{
public:
	virtual void SetSystemId( const char* system_id ) = 0;
	virtual void SetPassword( const char* password ) = 0;
	virtual void SetSystemType( const char* system_type ) = 0;

	virtual void SetInterfaceVersion( BYTE interface_version ) = 0;
	virtual void SetAddrTon( BYTE addr_ton ) = 0;
	virtual void SetAddrNpi( BYTE addr_npi ) = 0;
	virtual void SetAddressRange( const char* address_range  ) = 0;

	virtual const string& GetSystemId() = 0;
	virtual const string& GetPassword() = 0;
	virtual const string& GetSystemType() = 0;

	virtual BYTE GetInterfaceVersion() = 0;
	virtual BYTE GetAddrTon() = 0;
	virtual BYTE GetAddrNpi() = 0;
	virtual const string& GetAddressRange() = 0;

DECLARE_CH_REFCOUNTING( IPDUBindTransmitter )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////