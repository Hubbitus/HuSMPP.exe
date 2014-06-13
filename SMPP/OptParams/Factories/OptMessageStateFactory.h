////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptMessageStateFactory.h
// Pavel Alexeev	2007-11-29 02:15
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTMessageState.h"
////////////////////////////////////////////////////////
class IOptMessageStateFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptMessageStateFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////