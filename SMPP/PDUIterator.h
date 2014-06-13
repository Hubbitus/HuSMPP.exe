////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUIterator.h

#ifndef __PDUITERATOR_H__
#define __PDUITERATOR_H__

////////////////////////////////////////////////////////
//-1#include "SMPPHeader.h"
#include "../HuSMPPshared.h"
#include "PDU.h"

////////////////////////////////////////////////////////
class IPDUIterator
{
public:
  virtual bool More() = 0;
  virtual CH<IPDU> Next() = 0;
  virtual CH<IPDU> Peek() = 0;
  virtual void Rewind() = 0;

  virtual void PutPDU( CH<IPDU> pdu ) = 0;


  DECLARE_CH_REFCOUNTING( IPDUIterator )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
