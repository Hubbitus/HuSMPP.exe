////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmRespFactory.h

#ifndef __PDUDeliverSmRespFACTORY_H__
#define __PDUDeliverSmRespFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUDeliverSmRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUDeliverSmRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
