////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEConcatenated_longFactory.cpp
// Pavel Alexeev
// Created 2007-06-27 17:08
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../../../HuSMPPshared.h"
#include "IEConcatenated_longFactory.h"
#include "../IEConcatenated_long.h"
////////////////////////////////////////////////////////

class CIEConcatenated_longFactoryImpl : public IIEConcatenated_longFactory{
public:
	CIEConcatenated_longFactoryImpl();
	virtual ~CIEConcatenated_longFactoryImpl();

IEFACTORY_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IIEConcatenated_longFactory, CIEConcatenated_longFactoryImpl )

////////////////////////////////////////////////////////
CIEConcatenated_longFactoryImpl::CIEConcatenated_longFactoryImpl()
	: m_IEI ( UDH_IE_concatenated_long ){
}

////////////////////////////////////////////////////////
CIEConcatenated_longFactoryImpl::~CIEConcatenated_longFactoryImpl(){
}

////////////////////////////////////////////////////////
CH<IIE>
CIEConcatenated_longFactoryImpl::Make( CH<IRawBuffer> rawBuff ){
CH<IEConcatenated_long> retVal;

retVal->Initialize( rawBuff );
return SafeCastCH<IIE, IEConcatenated_long>( retVal );
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////