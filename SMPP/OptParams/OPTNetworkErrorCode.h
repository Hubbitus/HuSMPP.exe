////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTNetworkErrorCode.h
// Pavel Alexeev	2007-11-29 02:15
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class OPTNetworkErrorCode : public IPDUOptionalParameter{
public:
	enum { UNDEFINED = -1, ANSI_136 = 1, IS_95 = 2, GSM = 3, Reserved = 4 };

	//3 - GSM
	BYTE GetErrorType(){return (BYTE)((m_realValue >> 16) & 0x00FF);};
	WORD GetErrorCode(){return (WORD)(m_realValue & 0x0000FFFF);};

OPT_BASICS_DECLARATION(DWORD, PDU_OPT_NetworkErrorCode)
DECLARE_CH_REFCOUNTING( OPTNetworkErrorCode )

public:
	using IPDUOptionalParameter::Initialize;
	virtual void Initialize( REALTYPE val ) =0;
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////