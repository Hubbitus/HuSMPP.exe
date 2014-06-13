////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEUnknown.cpp
// Pavel Alexeev
// Created 2007-06-27 16:33
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEUnknown.h"
#include <sstream>
////////////////////////////////////////////////////////

class IEUnknownImpl : public IEUnknown {
public:
	IEUnknownImpl();
	virtual ~IEUnknownImpl();

IE_BASICS_DECLARATION( BYTE )
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IEUnknown, IEUnknownImpl )

IE_BASICS_DEFINITION( IEUnknownImpl, BYTE )

////////////////////////////////////////////////////////
IEUnknownImpl::IEUnknownImpl()
	: m_IEI ( UDH_IE_unknown ){
}

////////////////////////////////////////////////////////
IEUnknownImpl::~IEUnknownImpl(){
}

////////////////////////////////////////////////////////
void
IEUnknownImpl::parseRealValues(){
}

////////////////////////////////////////////////////////
IEUnknownImpl::operator std::string () {
std::ostringstream lStringOS;
lStringOS.setf(std::ostringstream::hex, std::ostringstream::basefield);
lStringOS.setf(std::ostringstream::showbase);
lStringOS << "IE Unknown -" << GetIEI() << '(' << std::dec << GetIEI() << ')';
return lStringOS.str();
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////