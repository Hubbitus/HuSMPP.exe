////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameterIterator.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../HuSMPPshared.h"
//#include "CmnHdr.h"

//#include "PDUOptionalParameterIterator.h"
#include "SMPPSessionState.h"

#include <vector>

////////////////////////////////////////////////////////
class CPDUOptionalParameterIteratorImpl : public IPDUOptionalParameterIterator
{
public:
  //
  CPDUOptionalParameterIteratorImpl();
  virtual ~CPDUOptionalParameterIteratorImpl();

  //
  virtual bool More();
  virtual CH<IPDUOptionalParameter> Next();
  virtual CH<IPDUOptionalParameter> Peek();
  virtual void Rewind();
  virtual void PutOptParam( CH<IPDUOptionalParameter> optParam );

private:
  std::vector<CH<IPDUOptionalParameter> > m_PDUOptionalParameters;
  unsigned int m_CurrentPosition;
  
  CH<IPDUOptionalParameter> m_MiscValue;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUOptionalParameterIterator, CPDUOptionalParameterIteratorImpl )

////////////////////////////////////////////////////////
CPDUOptionalParameterIteratorImpl::CPDUOptionalParameterIteratorImpl()
{
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
CPDUOptionalParameterIteratorImpl::~CPDUOptionalParameterIteratorImpl()
{
  m_PDUOptionalParameters.clear();
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
bool 
CPDUOptionalParameterIteratorImpl::More()
{
  bool retVal = ( m_CurrentPosition < m_PDUOptionalParameters.size() );
  return retVal;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
CPDUOptionalParameterIteratorImpl::Next()
{
  CH<IPDUOptionalParameter> retVal = m_MiscValue;

  if ( More() )
  {
    retVal = m_PDUOptionalParameters[ m_CurrentPosition ];
    m_CurrentPosition++;
  }

  return retVal;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
CPDUOptionalParameterIteratorImpl::Peek()
{
  CH<IPDUOptionalParameter> retVal = m_MiscValue;

  if ( More() )
    retVal = m_PDUOptionalParameters[ m_CurrentPosition ];

  return retVal;
}

////////////////////////////////////////////////////////
void
CPDUOptionalParameterIteratorImpl::Rewind()
{
  m_CurrentPosition = 0;
}

////////////////////////////////////////////////////////
void
CPDUOptionalParameterIteratorImpl::PutOptParam( CH<IPDUOptionalParameter> optParam )
{
  m_PDUOptionalParameters.push_back( optParam );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////