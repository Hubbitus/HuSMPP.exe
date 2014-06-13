////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMPPSessionOpenState.h
// Added by: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../HuSMPPClient.h"
#include "../SMPPSessionState.h"
#include "../../HuSMSCConfig.h"

////////////////////////////////////////////////////////
class ISMPPSessionOpenState : public ISMPPSessionState{
public:
	virtual void Initialize( SP<ISMPPClient> client ) = 0;

DECLARE_CH_REFCOUNTING( ISMPPSessionOpenState )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////