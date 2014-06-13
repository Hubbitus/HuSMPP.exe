////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOutbindFactory.h

#ifndef __PDUOUTBINDFACTORY_H__
#define __PDUOUTBINDFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUOutbindFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUOutbindFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
