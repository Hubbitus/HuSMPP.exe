////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptReceiptedMessageIdFactory.cpp
// Pavel Alexeev	2007-11-29 02:42
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptReceiptedMessageIdFactory.h"
////////////////////////////////////////////////////////

class COptReceiptedMessageIdFactoryImpl : public IOptReceiptedMessageIdFactory{
public:
	COptReceiptedMessageIdFactoryImpl();
	virtual ~COptReceiptedMessageIdFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptReceiptedMessageIdFactory, COptReceiptedMessageIdFactoryImpl )

////////////////////////////////////////////////////////
COptReceiptedMessageIdFactoryImpl::COptReceiptedMessageIdFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptReceiptedMessageIdFactoryImpl::~COptReceiptedMessageIdFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptReceiptedMessageIdFactoryImpl::GetTagId()
{
  return PDU_OPT_ReceiptedMessageId;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptReceiptedMessageIdFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTReceiptedMessageId> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTReceiptedMessageId>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////