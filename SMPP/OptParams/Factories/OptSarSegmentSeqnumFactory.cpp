////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarSegmentSeqnumFactory.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptSarSegmentSeqnumFactory.h"

////////////////////////////////////////////////////////
class COptSarSegmentSeqnumFactoryImpl : public IOptSarSegmentSeqnumFactory{
public:
COptSarSegmentSeqnumFactoryImpl();
virtual ~COptSarSegmentSeqnumFactoryImpl();

virtual WORD GetTagId(){return PDU_OPT_SarSegmentSeqnum;};
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptSarSegmentSeqnumFactory, COptSarSegmentSeqnumFactoryImpl )

////////////////////////////////////////////////////////
COptSarSegmentSeqnumFactoryImpl::COptSarSegmentSeqnumFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptSarSegmentSeqnumFactoryImpl::~COptSarSegmentSeqnumFactoryImpl()
{
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptSarSegmentSeqnumFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTSarSegmentSeqnum> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTSarSegmentSeqnum> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////