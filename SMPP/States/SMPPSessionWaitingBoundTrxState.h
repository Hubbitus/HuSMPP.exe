////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionWaitingBoundTrxState.h

#ifndef __SMPPSESSIONWAITINGBOUNDTRXSTATE_H__
#define __SMPPSESSIONWAITINGBOUNDTRXSTATE_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../../SMPP/SMPPSessionState.h"

////////////////////////////////////////////////////////
class ISMPPSessionWaitingBoundTrxState : public ISMPPSessionState
{
public:
  virtual void Initialize( SP<ISMPPClient> client, DWORD sequenceNumber ) = 0;

  DECLARE_CH_REFCOUNTING( ISMPPSessionWaitingBoundTrxState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
