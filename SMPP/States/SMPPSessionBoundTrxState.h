////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundTrxState.h

#ifndef __SMPPSESSIONBOUNDTRXSTATE_H__
#define __SMPPSESSIONBOUNDTRXSTATE_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../SMPPSessionState.h"
////////////////////////////////////////////////////////
class ISMPPSessionBoundTrxState : public ISMPPSessionState{
public:
	virtual void Initialize( SP<ISMPPClient> client ) = 0;

DECLARE_CH_REFCOUNTING( ISMPPSessionBoundTrxState )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
