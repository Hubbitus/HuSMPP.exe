////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : UnbindAction.h

#ifndef __UnbindAction_H__
#define __UnbindAction_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "action.h"
#include "../../SMPP/PDU/PDUUnbind.h"

////////////////////////////////////////////////////////
class IUnbindAction : public IAction
{
public:
  virtual void Initialize( SP<IPDUUnbind> pdu, SP<ISMPPClient> client ) = 0;

  DECLARE_CH_REFCOUNTING( IUnbindAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
