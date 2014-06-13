////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptSourceSubaddressFactory.h
// Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTSourceSubaddress.h"

////////////////////////////////////////////////////////
class IOptSourceSubaddressFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptSourceSubaddressFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////