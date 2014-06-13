////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionWaitingUnbindState.h

#ifndef __SMPPSessionWaitingUnbindState_H__
#define __SMPPSessionWaitingUnbindState_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
////////////////////////////////////////////////////////
class ISMPPSessionWaitingUnbindState : public ISMPPSessionState{
public:
	virtual void Initialize( SP<ISMPPClient> client, DWORD sequenceNumber ) = 0;

DECLARE_CH_REFCOUNTING( ISMPPSessionWaitingUnbindState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////