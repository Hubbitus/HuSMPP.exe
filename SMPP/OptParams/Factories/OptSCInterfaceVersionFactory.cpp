////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OptSCInterfaceVersionFactory.cpp
// Pavel Alexeev	2008-01-15 09:22
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptSCInterfaceVersionFactory.h"

////////////////////////////////////////////////////////
class COptSCInterfaceVersionFactoryImpl : public IOptSCInterfaceVersionFactory{
public:
COptSCInterfaceVersionFactoryImpl();
virtual ~COptSCInterfaceVersionFactoryImpl();

virtual WORD GetTagId(){return PDU_OPT_SCInterfaceVersion;};
virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptSCInterfaceVersionFactory, COptSCInterfaceVersionFactoryImpl )

////////////////////////////////////////////////////////
COptSCInterfaceVersionFactoryImpl::COptSCInterfaceVersionFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptSCInterfaceVersionFactoryImpl::~COptSCInterfaceVersionFactoryImpl()
{
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptSCInterfaceVersionFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTSCInterfaceVersion> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTSCInterfaceVersion> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////