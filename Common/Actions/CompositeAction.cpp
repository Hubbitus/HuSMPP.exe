////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : compositeaction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_LastState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../CmnHdr.h"

#include "compositeaction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/PDU.h"

#include <vector>

////////////////////////////////////////////////////////

class CCompositeActionImpl : public ICompositeAction{
public:
	CCompositeActionImpl();
	virtual ~CCompositeActionImpl();

	virtual void Initialize();

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

	virtual void AddAction( CH<IAction> );

private:
	std::vector<CH<IAction> > m_Actions;
	CH<IPDU> m_LastResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ICompositeAction, CCompositeActionImpl )

////////////////////////////////////////////////////////
CCompositeActionImpl::CCompositeActionImpl(){
}

////////////////////////////////////////////////////////
CCompositeActionImpl::~CCompositeActionImpl(){
}

////////////////////////////////////////////////////////
void 
CCompositeActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CCompositeActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionState> lastState;
	for ( unsigned int i = 0; i < m_Actions.size(); i++ ){
	CH<IAction> action = m_Actions[ i ];
	lastState = action->Perform( pdu );

	m_LastResponse = action->GetResponse();
	}

return lastState;
}

////////////////////////////////////////////////////////
CH<IPDU>
CCompositeActionImpl::GetResponse(){
return m_LastResponse;
}

////////////////////////////////////////////////////////
void 
CCompositeActionImpl::AddAction( CH<IAction> action ){
m_Actions.push_back( action );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////