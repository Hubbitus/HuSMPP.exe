////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindTransmitterAction.h
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"
#include "../../SMPP/PDU/PDUBindTransmitter.h"

////////////////////////////////////////////////////////
class IBindTransmitterAction : public IAction{
public:
	virtual void Initialize( SP<IPDUBindTransmitter> pdu, SP<ISMPPClient> client ) = 0;

DECLARE_CH_REFCOUNTING( IBindTransmitterAction )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////