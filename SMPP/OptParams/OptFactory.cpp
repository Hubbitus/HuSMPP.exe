////////////////////////////////////////////////////////
// Project : SMPSample
// Module  : OptFactory.cpp
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../HuSMPPshared.h"
#include "OptFactory.h"

////////////////////////////////////////////////////////
class COptFactoryImpl : public IOptFactory{
public:
	COptFactoryImpl();
	virtual ~COptFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptFactory, COptFactoryImpl )

////////////////////////////////////////////////////////
COptFactoryImpl::COptFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptFactoryImpl::~COptFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptFactoryImpl::GetTagId(){
//*85 return PDU_OPT_INVALID;
return PDU_OPT_UNKNOWN;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<IPDUOptionalParameter> retVal;

retVal->Initialize( rawBuffer );
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////