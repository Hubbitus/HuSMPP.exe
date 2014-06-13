////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarTotalSegmentsFactory.h
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTSarTotalSegments.h"

////////////////////////////////////////////////////////
class IOptSarTotalSegmentsFactory : public IOptFactory{
public:

virtual WORD GetTagId() = 0;
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptSarTotalSegmentsFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////