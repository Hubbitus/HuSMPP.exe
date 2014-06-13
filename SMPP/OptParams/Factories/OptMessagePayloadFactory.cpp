////////////////////////////////////////////////////////
// Project : SMPSample
// Module  : OptMessagePayloadFactory.cpp
// Pavel Alexeev
// Created 2007-06-28 23:52
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptMessagePayloadFactory.h"

////////////////////////////////////////////////////////
class COptMessagePayloadFactoryImpl : public IOptMessagePayloadFactory{
public:
	COptMessagePayloadFactoryImpl();
	virtual ~COptMessagePayloadFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptMessagePayloadFactory, COptMessagePayloadFactoryImpl )

////////////////////////////////////////////////////////
COptMessagePayloadFactoryImpl::COptMessagePayloadFactoryImpl(){
}

////////////////////////////////////////////////////////
COptMessagePayloadFactoryImpl::~COptMessagePayloadFactoryImpl(){
}

////////////////////////////////////////////////////////
WORD
COptMessagePayloadFactoryImpl::GetTagId(){
return PDU_OPT_MessagePayload;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptMessagePayloadFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTMessagePayload> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTMessagePayload>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////