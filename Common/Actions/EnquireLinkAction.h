////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : EnquireLinkAction.h

#ifndef __EnquireLinkAction_H__
#define __EnquireLinkAction_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

////////////////////////////////////////////////////////
class IEnquireLinkAction : public IAction{
public:
	virtual void Initialize( SP<ISMPPClient> client, SP<IPDU> pdu ) = 0;

DECLARE_CH_REFCOUNTING( IEnquireLinkAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////