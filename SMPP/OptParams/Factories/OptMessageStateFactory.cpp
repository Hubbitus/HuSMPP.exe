////////////////////////////////////////////////////////
// Project : HuSMPS.exe
// Module  : OptMessageStateFactory.cpp
// Pavel Alexeev	2007-11-29 02:15
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../HuSMPPshared.h"
#include "../OptFactory.h"
#include "OptMessageStateFactory.h"
////////////////////////////////////////////////////////
class COptMessageStateFactoryImpl : public IOptMessageStateFactory{
public:
	COptMessageStateFactoryImpl();
	virtual ~COptMessageStateFactoryImpl();

	virtual WORD GetTagId();
	virtual CH<IPDUOptionalParameter> Make( CH<IRawBuffer> rawBuffer);
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOptMessageStateFactory, COptMessageStateFactoryImpl )

////////////////////////////////////////////////////////
COptMessageStateFactoryImpl::COptMessageStateFactoryImpl()
{
}

////////////////////////////////////////////////////////
COptMessageStateFactoryImpl::~COptMessageStateFactoryImpl()
{
}

////////////////////////////////////////////////////////
WORD
COptMessageStateFactoryImpl::GetTagId(){
  return PDU_OPT_MessageState;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
COptMessageStateFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<OPTMessageState> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IPDUOptionalParameter, OPTMessageState> ( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////