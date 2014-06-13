////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : UnbindRespAction.h

#ifndef __UnbindRespAction_H__
#define __UnbindRespAction_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

/*-52
#include "../../HuSMPPshared.h"

#include "action.h"
#include "../../SMPP/PDU/PDUUnbindResp.h"
*/
////////////////////////////////////////////////////////
class IUnbindRespAction : public IAction
{
public:
  virtual void Initialize( SP<IPDUUnbindResp> pdu, SP<ISMPPClient> client ) = 0;

  DECLARE_CH_REFCOUNTING( IUnbindRespAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
