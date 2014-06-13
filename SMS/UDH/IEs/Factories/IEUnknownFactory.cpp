////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEUnknownFactory.cpp
// Pavel Alexeev
// Created 2007-06-27 14:23
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEUnknownFactory.h"
#include "../IEUnknown.h"
////////////////////////////////////////////////////////

class CIEUnknownFactoryImpl : public IIEUnknownFactory{
public:
	CIEUnknownFactoryImpl();
	virtual ~CIEUnknownFactoryImpl();

IEFACTORY_BASICS_DECLARATION	
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IIEUnknownFactory, CIEUnknownFactoryImpl )

////////////////////////////////////////////////////////
CIEUnknownFactoryImpl::CIEUnknownFactoryImpl(){
}

////////////////////////////////////////////////////////
CIEUnknownFactoryImpl::~CIEUnknownFactoryImpl(){
}

////////////////////////////////////////////////////////
CH<IIE>
CIEUnknownFactoryImpl::Make( CH<IRawBuffer> rawBuff ){
CH<IEUnknown> retVal;

retVal->Initialize( rawBuff );
return SafeCastCH<IIE, IEUnknown>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////