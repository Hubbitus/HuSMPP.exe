////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OptDeliverRouteFactory.h
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTDeliverRoute.h"

////////////////////////////////////////////////////////
class IOptDeliverRouteFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptDeliverRouteFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////