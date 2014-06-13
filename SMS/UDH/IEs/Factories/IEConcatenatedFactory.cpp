////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEConcatenatedFactory.cpp
// Pavel Alexeev
// Created 2007-06-27 17:08
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEConcatenatedFactory.h"
#include "../IEConcatenated.h"
////////////////////////////////////////////////////////

class CIEConcatenatedFactoryImpl : public IIEConcatenatedFactory{
public:
	CIEConcatenatedFactoryImpl();
	virtual ~CIEConcatenatedFactoryImpl();

//+74.2
//virtual CH<IIE> Make( CH<IRawBuffer> rawBuffer );

IEFACTORY_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IIEConcatenatedFactory, CIEConcatenatedFactoryImpl )

////////////////////////////////////////////////////////
CIEConcatenatedFactoryImpl::CIEConcatenatedFactoryImpl()
	: m_IEI ( UDH_IE_concatenated ){
}

////////////////////////////////////////////////////////
CIEConcatenatedFactoryImpl::~CIEConcatenatedFactoryImpl(){
}

////////////////////////////////////////////////////////
CH<IIE>
CIEConcatenatedFactoryImpl::Make( CH<IRawBuffer> rawBuffer ){
CH<IEConcatenated> retVal;

retVal->Initialize( rawBuffer );
return SafeCastCH<IIE, IEConcatenated>( retVal );
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////