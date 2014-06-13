////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTMessagePayload.h
// Pavel Alexeev
// Created 2007-06-28 23:52
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
////////////////////////////////////////////////////////

class OPTMessagePayload : public IPDUOptionalParameter{
public:
OPT_BASICS_DECLARATION(std::string, PDU_OPT_MessagePayload)
DECLARE_CH_REFCOUNTING( OPTMessagePayload )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////