////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : ForwardPDUAction.h

#ifndef __ForwardPDUAction_H__
#define __ForwardPDUAction_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

/*-52
#include "../../HuSMPPshared.h"

#include "action.h"
#include "../../SMPP/PDU.h"
*/
////////////////////////////////////////////////////////
class IForwardPDUAction : public IAction
{
public:
  virtual void Initialize( SP<ISMPPClient> client, SP<IPDU> pdu ) = 0;

  DECLARE_CH_REFCOUNTING( IForwardPDUAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
