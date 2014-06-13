////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEsIterator.h
// Pavel Alexeev
// Created 2007-06-27 15:11
////////////////////////////////////////////////////////

#pragma once

#include "IE.h"
////////////////////////////////////////////////////////

class IIEsIterator{
public:
	virtual bool More() = 0;
	virtual CH<IIE> Next() = 0;
	virtual CH<IIE> Peek() = 0;
	virtual void Rewind() = 0;

	virtual void PutIE( CH<IIE> ie ) = 0;

	DECLARE_CH_REFCOUNTING( IIEsIterator )
};
// =================== END OF FILE =====================
////////////////////////////////////////////////////////
