////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTMessageState.h
// Pavel Alexeev	2007-11-29 02:15
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
//
//	2008-09-01
//	- SymbNames changed according to SMPPv3.4 Apendix B, table B-2
//
//	2008-09-03
//	- std::map<DWORD, std::string> mutable SymbNames renamed to SymbNames_, made
//		private and moved to OPTMessageStateImpl class (.cpp file)
//	- initSymbNames() method made private. Moved implementation into .cpp file
//	- In enum OptStates add value UNDEFINED = 10
//	- GetSymbolicName() implementation moved into .cpp
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

#include <map>

////////////////////////////////////////////////////////
class OPTMessageState : public IPDUOptionalParameter{
public:
	//http://www.activexperts.com/activsms/sms/smppdeliveryreports/
	enum OptStates { SCHEDULED = 0, ENROUTE = 1, DELIVERED = 2, EXPIRED = 3, DELETED = 4, UNDELIVERABLE = 5, ACCEPTED = 6, UNKNOWN = 7, REJECTED = 8, SKIPPED = 9, /* MY addition */ UNDEFINED = 100 };

	//Primary for LOGS.
	virtual std::string GetSymbolicName( char state  = -1) =0;

OPT_BASICS_DECLARATION(WORD, PDU_OPT_MessageState)
DECLARE_CH_REFCOUNTING( OPTMessageState )

public:
	using IPDUOptionalParameter::Initialize;
	virtual void Initialize( REALTYPE val ) =0;
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////