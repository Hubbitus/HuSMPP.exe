////////////////////////////////////////////////////////
// Project : SMPSample
// Module  : OptUnknownFactory.cpp
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "OptUnknownFactory.h"
////////////////////////////////////////////////////////
class COptUnknownFactoryImpl : public IOptUnknownFactory{
public:
	COptUnknownFactoryImpl();
	virtual ~COptUnknownFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptUnknownFactory, COptUnknownFactoryImpl )

////////////////////////////////////////////////////////
COptUnknownFactoryImpl::COptUnknownFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptUnknownFactoryImpl::~COptUnknownFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptUnknownFactoryImpl::GetTagId()
{
  return PDU_OPT_UNKNOWN;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptUnknownFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTUnknown> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter,OPTUnknown>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////