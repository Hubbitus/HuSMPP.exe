////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptSCInterfaceVersionFactory.h
// Pavel Alexeev	2008-01-15 09:22
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTSCInterfaceVersion.h"

////////////////////////////////////////////////////////
class IOptSCInterfaceVersionFactory : public IOptFactory{
public:

virtual WORD GetTagId() = 0;
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptSCInterfaceVersionFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////