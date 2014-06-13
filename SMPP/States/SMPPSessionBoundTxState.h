////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundTxState.h

#ifndef __SMPPSESSIONBOUNDTXSTATE_H__
#define __SMPPSESSIONBOUNDTXSTATE_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"

////////////////////////////////////////////////////////
class ISMPPSessionBoundTxState : public ISMPPSessionState
{
public:
  DECLARE_CH_REFCOUNTING( ISMPPSessionBoundTxState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
