////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptSourceSubaddressFactory.cpp
// Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptSourceSubaddressFactory.h"

////////////////////////////////////////////////////////
class COptSourceSubaddressFactoryImpl : public IOptSourceSubaddressFactory{
public:
	COptSourceSubaddressFactoryImpl();
	virtual ~COptSourceSubaddressFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptSourceSubaddressFactory, COptSourceSubaddressFactoryImpl )

////////////////////////////////////////////////////////
COptSourceSubaddressFactoryImpl::COptSourceSubaddressFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptSourceSubaddressFactoryImpl::~COptSourceSubaddressFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptSourceSubaddressFactoryImpl::GetTagId()
{
  return PDU_OPT_SourceSubaddress;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptSourceSubaddressFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTSourceSubaddress> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTSourceSubaddress>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////