////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptReceiptedMessageIdFactory.h
// Pavel Alexeev	2007-11-29 02:15
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../../HuSMPPshared.h"
#include "../../../Utils/rawbuffer.h"
#include "../../PDUOptionalParameter.h"
#include "../OPTReceiptedMessageId.h"

////////////////////////////////////////////////////////
class IOptReceiptedMessageIdFactory : public IOptFactory{
public:
	virtual WORD GetTagId() = 0;
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer ) = 0;

DECLARE_CH_REFCOUNTING( IOptReceiptedMessageIdFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////