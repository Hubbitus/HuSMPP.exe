////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEFactory.h
// Pavel Alexeev
// Created 2007-06-27 14:23
////////////////////////////////////////////////////////
#pragma once

#include "IE.h"
////////////////////////////////////////////////////////
#define IEFACTORY_BASICS_DECLARATION \
protected: \
	int m_IEI; \
public: \
	virtual int GetIEI(){return m_IEI;}; \
	virtual CH<IIE> Make( CH<IRawBuffer> rawBuff );

class IIEFactory{
public:
	virtual CH<IIE> Make( CH<IRawBuffer> rawBuffer ) = 0;
	virtual int GetIEI(){return m_IEI;};

protected:
	int m_IEI;
DECLARE_CH_REFCOUNTING( IIEFactory )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////