////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmFactory.h

#ifndef __PDUDeliverSmFACTORY_H__
#define __PDUDeliverSmFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUDeliverSmFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUDeliverSmFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
