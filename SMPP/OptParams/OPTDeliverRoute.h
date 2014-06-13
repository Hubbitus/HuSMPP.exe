////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTDeliverRoute.h
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
////////////////////////////////////////////////////////

class OPTDeliverRoute : public IPDUOptionalParameter{
public:
OPT_BASICS_DECLARATION(std::string, PDU_OPT_DeliverRoute)
DECLARE_CH_REFCOUNTING( OPTDeliverRoute )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////