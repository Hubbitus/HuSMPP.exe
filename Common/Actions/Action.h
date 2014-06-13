////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : action.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

class IAction;
class ISMPPSessionState;

#include "../../HuSMPPshared.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/PDU.h"

////////////////////////////////////////////////////////

class IAction{
public:
	virtual void Initialize() = 0;

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu ) = 0;
	virtual CH<IPDU> GetResponse() = 0;

	DECLARE_CH_REFCOUNTING( IAction )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////