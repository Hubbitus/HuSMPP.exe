////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDataSmRespFactory.h

#ifndef __PDUDataSmRespFACTORY_H__
#define __PDUDataSmRespFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUDataSmRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUDataSmRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
