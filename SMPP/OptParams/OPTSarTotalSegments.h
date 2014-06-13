////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarTotalSegments.h
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class OPTSarTotalSegments : public IPDUOptionalParameter{
public:

OPT_BASICS_DECLARATION( BYTE, PDU_OPT_SarTotalSegments )
DECLARE_CH_REFCOUNTING( OPTSarTotalSegments )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////