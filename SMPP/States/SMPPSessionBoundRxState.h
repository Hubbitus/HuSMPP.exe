////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundRxState.h

#ifndef __SMPPSESSIONBOUNDRXSTATE_H__
#define __SMPPSESSIONBOUNDRXSTATE_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////
class ISMPPSessionBoundRxState : public ISMPPSessionState
{
public:
  DECLARE_CH_REFCOUNTING( ISMPPSessionBoundRxState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
