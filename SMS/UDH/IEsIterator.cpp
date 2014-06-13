////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEsIterator.cpp
// Pavel Alexeev
// Created 2007-06-27 15:23
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEsIterator.h"

#include <vector>
////////////////////////////////////////////////////////

class CIEsIteratorImpl : public IIEsIterator{
public:
	CIEsIteratorImpl();
	virtual ~CIEsIteratorImpl();

	virtual bool More();
	virtual CH<IIE> Next();
	virtual CH<IIE> Peek();
	virtual void Rewind();
	virtual void PutIE( CH<IIE> ie );

protected:
private:
	std::vector< CH<IIE> > m_IEs;
	unsigned int m_CurrentPosition;

//-74.1
//	CH<IIE> m_MiscValue;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IIEsIterator, CIEsIteratorImpl )

////////////////////////////////////////////////////////
CIEsIteratorImpl::CIEsIteratorImpl(){
m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
CIEsIteratorImpl::~CIEsIteratorImpl(){
m_IEs.clear();
m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
bool 
CIEsIteratorImpl::More(){
return (bool)( m_CurrentPosition < m_IEs.size() );
}

////////////////////////////////////////////////////////
CH<IIE>
CIEsIteratorImpl::Next(){
//-74.1
//CH<IIE> retVal = m_MiscValue;
CH<IIE> retVal;
retVal = Peek();
m_CurrentPosition++;
return retVal;
}

////////////////////////////////////////////////////////
CH<IIE>
CIEsIteratorImpl::Peek(){
//-74.1
//CH<IIE> retVal = m_MiscValue;
CH<IIE> retVal;

	if ( More() ){
	retVal = m_IEs[ m_CurrentPosition ];
	}

return retVal;
}

////////////////////////////////////////////////////////
void
CIEsIteratorImpl::Rewind(){
m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
void
CIEsIteratorImpl::PutIE( CH<IIE> ie )
{
m_IEs.push_back( ie );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////