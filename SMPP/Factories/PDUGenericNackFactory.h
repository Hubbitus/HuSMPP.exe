////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUGenericNackFactory.h

#ifndef __PDUGENERICNACKFACTORY_H__
#define __PDUGENERICNACKFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUGenericNackFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUGenericNackFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
