////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : action.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

////////////////////////////////////////////////////////

class CActionImpl : public IAction{
public:
	CActionImpl();
	virtual ~CActionImpl();

	virtual void Initialize();

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );

	virtual CH<IPDU> GetResponse();
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IAction, CActionImpl )

////////////////////////////////////////////////////////
CActionImpl::CActionImpl(){
#pragma chMSG( Fix it later )
}

////////////////////////////////////////////////////////
CActionImpl::~CActionImpl(){
}

////////////////////////////////////////////////////////
void 
CActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CActionImpl::Perform( CH<IPDU> pdu ){
//AsIs
return pdu->GetInSocket()->getSessionState();
}

////////////////////////////////////////////////////////
CH<IPDU>
CActionImpl::GetResponse(){
CH<IPDU> retVal;
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////