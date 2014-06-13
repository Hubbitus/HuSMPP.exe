////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarTotalSegmentsFactory.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptSarTotalSegmentsFactory.h"

////////////////////////////////////////////////////////
class COptSarTotalSegmentsFactoryImpl : public IOptSarTotalSegmentsFactory{
public:
COptSarTotalSegmentsFactoryImpl();
virtual ~COptSarTotalSegmentsFactoryImpl();

virtual WORD GetTagId(){return PDU_OPT_SarTotalSegments;};
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptSarTotalSegmentsFactory, COptSarTotalSegmentsFactoryImpl )

////////////////////////////////////////////////////////
COptSarTotalSegmentsFactoryImpl::COptSarTotalSegmentsFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptSarTotalSegmentsFactoryImpl::~COptSarTotalSegmentsFactoryImpl()
{
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptSarTotalSegmentsFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTSarTotalSegments> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTSarTotalSegments> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////