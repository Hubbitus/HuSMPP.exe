////////////////////////////////////////////////////////
// Project : SMPSample
// Module  : OptUserResponseCodeFactory.cpp
//Pavel Alexeev
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptUserResponseCodeFactory.h"
////////////////////////////////////////////////////////
// COptFactoryImpl class
class COptUserResponseCodeFactoryImpl : public IOptUserResponseCodeFactory{
public:
	COptUserResponseCodeFactoryImpl();
	virtual ~COptUserResponseCodeFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptUserResponseCodeFactory, COptUserResponseCodeFactoryImpl )

////////////////////////////////////////////////////////
COptUserResponseCodeFactoryImpl::COptUserResponseCodeFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptUserResponseCodeFactoryImpl::~COptUserResponseCodeFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptUserResponseCodeFactoryImpl::GetTagId()
{
  return PDU_OPT_UserResponseCode;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptUserResponseCodeFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTUserResponseCode> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTUserResponseCode> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////