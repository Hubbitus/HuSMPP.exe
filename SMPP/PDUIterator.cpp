////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUIterator.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../HuSMPPshared.h"
#include "SMPPSessionState.h"
#include "PDUIterator.h"

#include <vector>
////////////////////////////////////////////////////////

class CPDUIteratorImpl : public IPDUIterator
{
public:
  //
  CPDUIteratorImpl();
  virtual ~CPDUIteratorImpl();

  //
  virtual bool More();

  virtual CH<IPDU> Next();
  virtual CH<IPDU> Peek();

  virtual void Rewind();

  virtual void PutPDU( CH<IPDU> pdu );

protected:
  //

private:
  // private member functions
  // private fields
  std::vector<CH<IPDU> > m_PDUs;
  unsigned int m_CurrentPosition;
  
  CH<IPDU> m_MiscValue;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUIterator, CPDUIteratorImpl )

////////////////////////////////////////////////////////
CPDUIteratorImpl::CPDUIteratorImpl()
{
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
CPDUIteratorImpl::~CPDUIteratorImpl()
{
  m_PDUs.clear();
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
bool 
CPDUIteratorImpl::More()
{
  bool retVal = ( m_CurrentPosition < m_PDUs.size() );
  return retVal;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUIteratorImpl::Next()
{
  CH<IPDU> retVal = m_MiscValue;

  if ( More() )
  {
    retVal = m_PDUs[ m_CurrentPosition ];
    m_CurrentPosition++;
  }

  return retVal;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUIteratorImpl::Peek()
{
  CH<IPDU> retVal = m_MiscValue;

  if ( More() )
    retVal = m_PDUs[ m_CurrentPosition ];

  return retVal;
}

////////////////////////////////////////////////////////
void
CPDUIteratorImpl::Rewind()
{
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
void
CPDUIteratorImpl::PutPDU( CH<IPDU> pdu )
{
  m_PDUs.push_back( pdu );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
