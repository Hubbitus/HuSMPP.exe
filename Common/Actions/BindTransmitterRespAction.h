////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindTransmitterRespAction.h
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

////////////////////////////////////////////////////////
class IBindTransmitterRespAction : public IAction{
public:
	virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindTransmitterResp> pdu ) = 0;

DECLARE_CH_REFCOUNTING( IBindTransmitterRespAction )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////