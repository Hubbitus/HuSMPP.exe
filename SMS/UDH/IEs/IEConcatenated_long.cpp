////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEConcatenated_long.cpp
// Pavel Alexeev
// Created 2007-06-27 16:45
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEConcatenated_long.h"
#include <sstream>
////////////////////////////////////////////////////////

class IEConcatenated_longImpl : public IEConcatenated_long{
public:
	IEConcatenated_longImpl();
	virtual ~IEConcatenated_longImpl();

IE_BASICS_DECLARATION( BYTE )
};

////////////////////////////////////////////////////////

IMPLEMENT_CH_REFCOUNTING( IEConcatenated_long, IEConcatenated_longImpl )

IE_BASICS_DEFINITION( IEConcatenated_longImpl, BYTE )

////////////////////////////////////////////////////////
IEConcatenated_longImpl::IEConcatenated_longImpl()
	: m_IEI ( UDH_IE_concatenated_long ){
#pragma chMSG( Fix it later IF needed )
m_msgPartLinkID = 0;
m_msgPartsTotal = 1;
m_msgPartNo = 1;
}

////////////////////////////////////////////////////////
IEConcatenated_longImpl::~IEConcatenated_longImpl(){
}

////////////////////////////////////////////////////////
void
IEConcatenated_longImpl::parseRealValues(){
CH<IRawBuffer> tmpBuff = m_Value->Clone();
//вот оно, самое главное отличие от не long!
m_msgPartLinkID = tmpBuff->GetWORD();

m_msgPartsTotal = tmpBuff->GetBYTE();
m_msgPartNo = tmpBuff->GetBYTE();
}

////////////////////////////////////////////////////////
IEConcatenated_longImpl::operator std::string () {
std::ostringstream lStringOS;
lStringOS << "IE Conc_long: " << "LinkID=" << m_msgPartLinkID << " Part: " << m_msgPartNo << '/' << m_msgPartsTotal;

return lStringOS.str();
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////