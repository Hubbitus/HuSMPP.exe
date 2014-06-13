////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OptFactoryMessagePayloadFactory.h
// Pavel Alexeev
// Created 2007-06-28 23:52
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTMessagePayload.h"

///////
//http://www.isms.ru/article.shtml?/smpp/smpp_153
////////////////////////////////////////////////////////
class IOptMessagePayloadFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptMessagePayloadFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////