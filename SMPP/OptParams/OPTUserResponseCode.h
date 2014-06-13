////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTUserResponseCode.h
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class OPTUserResponseCode : public IPDUOptionalParameter{
public:
OPT_BASICS_DECLARATION(WORD, PDU_OPT_UserResponseCode)
DECLARE_CH_REFCOUNTING( OPTUserResponseCode )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////