////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : bindtransceiveraction.h

#ifndef __BINDTRANSCEIVERACTION_H__
#define __BINDTRANSCEIVERACTION_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"
#include "../../SMPP/PDU/PDUBindTransceiver.h"

////////////////////////////////////////////////////////
class IBindTransceiverAction : public IAction
{
public:
  virtual void Initialize( SP<IPDUBindTransceiver> pdu, SP<ISMPPClient> client ) = 0;

  DECLARE_CH_REFCOUNTING( IBindTransceiverAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
