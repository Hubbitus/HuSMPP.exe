////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : bindtransceiverrespaction.h

#ifndef __BINDTRANSCEIVERRESPACTION_H__
#define __BINDTRANSCEIVERRESPACTION_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

/*-52
#include "../../HuSMPPshared.h"

#include "action.h"
#include "../../SMPP/PDU/PDUBindTransceiverResp.h"
*/
////////////////////////////////////////////////////////
class IBindTransceiverRespAction : public IAction
{
public:
  virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindTransceiverResp> pdu ) = 0;

  DECLARE_CH_REFCOUNTING( IBindTransceiverRespAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
