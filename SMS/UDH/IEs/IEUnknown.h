////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEUnknown.h
// Pavel Alexeev
// Created 2007-06-27 16:19
////////////////////////////////////////////////////////
#pragma once

#include "../IE.h"
////////////////////////////////////////////////////////

class IEUnknown : public IIE{
//	virtual void parseRealValues() = 0;
public:
	DECLARE_CH_REFCOUNTING( IEUnknown )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////