////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindReceiverRespAction.h
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

////////////////////////////////////////////////////////
class IBindReceiverRespAction : public IAction{
public:
	virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindReceiverResp> pdu ) = 0;

DECLARE_CH_REFCOUNTING( IBindReceiverRespAction )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////