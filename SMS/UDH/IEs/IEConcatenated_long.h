////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEConcatenated_long.h
// Pavel Alexeev
// Created 2007-06-27 16:46
////////////////////////////////////////////////////////
#pragma once

#include "../IE.h"
////////////////////////////////////////////////////////

class IEConcatenated_long : public IIE{
	virtual void parseRealValues() = 0;
public:
	virtual WORD msgPartLinkID (){return m_msgPartLinkID;};
	virtual WORD msgPartsTotal (){return m_msgPartsTotal;};
	virtual WORD msgPartNo (){return m_msgPartNo;};
protected:
	WORD m_msgPartLinkID;
	WORD m_msgPartsTotal;
	WORD m_msgPartNo;

DECLARE_CH_REFCOUNTING( IEConcatenated_long )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////