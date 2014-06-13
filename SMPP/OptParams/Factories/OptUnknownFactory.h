////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OptUnknownFactory.h
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
// Changed: 2008-01-16
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "../OPTUnknown.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class IOptUnknownFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptUnknownFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////