////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OptDeliverRouteFactory.cpp
//Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptDeliverRouteFactory.h"

////////////////////////////////////////////////////////
class COptDeliverRouteFactoryImpl : public IOptDeliverRouteFactory{
public:
	COptDeliverRouteFactoryImpl();
	virtual ~COptDeliverRouteFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptDeliverRouteFactory, COptDeliverRouteFactoryImpl )

////////////////////////////////////////////////////////
COptDeliverRouteFactoryImpl::COptDeliverRouteFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptDeliverRouteFactoryImpl::~COptDeliverRouteFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptDeliverRouteFactoryImpl::GetTagId()
{
  return PDU_OPT_DeliverRoute;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptDeliverRouteFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTDeliverRoute> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTDeliverRoute>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////