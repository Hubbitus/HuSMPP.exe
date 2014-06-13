////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDataSmFactory.h

#ifndef __PDUDataSmFACTORY_H__
#define __PDUDataSmFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUDataSmFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUDataSmFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
