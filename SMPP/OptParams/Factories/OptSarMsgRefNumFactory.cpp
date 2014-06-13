////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarMsgRefNumFactory.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptSarMsgRefNumFactory.h"

////////////////////////////////////////////////////////
class COptSarMsgRefNumFactoryImpl : public IOptSarMsgRefNumFactory{
public:
COptSarMsgRefNumFactoryImpl();
virtual ~COptSarMsgRefNumFactoryImpl();

virtual WORD GetTagId(){return PDU_OPT_SarMsgRefNum;};
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptSarMsgRefNumFactory, COptSarMsgRefNumFactoryImpl )

////////////////////////////////////////////////////////
COptSarMsgRefNumFactoryImpl::COptSarMsgRefNumFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptSarMsgRefNumFactoryImpl::~COptSarMsgRefNumFactoryImpl()
{
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptSarMsgRefNumFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTSarMsgRefNum> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTSarMsgRefNum> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////