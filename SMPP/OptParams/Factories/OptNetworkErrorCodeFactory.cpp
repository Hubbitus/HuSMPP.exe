////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptNetworkErrorCodeFactory.cpp
// Pavel Alexeev	2007-11-29 02:15
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptNetworkErrorCodeFactory.h"

////////////////////////////////////////////////////////
class COptNetworkErrorCodeFactoryImpl : public IOptNetworkErrorCodeFactory{
public:
  COptNetworkErrorCodeFactoryImpl();
  virtual ~COptNetworkErrorCodeFactoryImpl();

  virtual WORD GetTagId();
  virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptNetworkErrorCodeFactory, COptNetworkErrorCodeFactoryImpl )

////////////////////////////////////////////////////////
COptNetworkErrorCodeFactoryImpl::COptNetworkErrorCodeFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptNetworkErrorCodeFactoryImpl::~COptNetworkErrorCodeFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptNetworkErrorCodeFactoryImpl::GetTagId(){
  return PDU_OPT_NetworkErrorCode;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptNetworkErrorCodeFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTNetworkErrorCode> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTNetworkErrorCode> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////