////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindReceiverAction.h
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"
#include "../../SMPP/PDU/PDUBindReceiver.h"

////////////////////////////////////////////////////////
class IBindReceiverAction : public IAction{
public:
	virtual void Initialize( SP<IPDUBindReceiver> pdu, SP<ISMPPClient> client ) = 0;

DECLARE_CH_REFCOUNTING( IBindReceiverAction )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////