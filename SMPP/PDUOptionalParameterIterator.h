////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameterIterator.h

#ifndef __PDUOptionalParameterIterator_H__
#define __PDUOptionalParameterIterator_H__

////////////////////////////////////////////////////////
#include "PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class IPDUOptionalParameterIterator
{
public:
  virtual bool More() = 0;
  virtual CH<IPDUOptionalParameter> Next() = 0;
  virtual CH<IPDUOptionalParameter> Peek() = 0;
  virtual void Rewind() = 0;

  virtual void PutOptParam( CH<IPDUOptionalParameter> optParam ) = 0;

  DECLARE_CH_REFCOUNTING( IPDUOptionalParameterIterator )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////