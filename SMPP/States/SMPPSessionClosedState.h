////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionClosedState.h

#ifndef __SMPPSESSIONCLOSEDSTATE_H__
#define __SMPPSESSIONCLOSEDSTATE_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../HuSMPPClient.h"
#include "../SMPPSessionState.h"
#include "../../HuSMSCConfig.h"

////////////////////////////////////////////////////////
class ISMPPSessionClosedState : public ISMPPSessionState
{
public:
  virtual void Initialize( SP<ISMPPClient> client ) = 0;

  DECLARE_CH_REFCOUNTING( ISMPPSessionClosedState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
