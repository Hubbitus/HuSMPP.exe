////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : UnbindAction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../../SMPP/SMPPSessionState.h"
#include "UnbindAction.h"

//-90 #include "../../SMPP/States/SMPPSessionWaitingUnbindState.h"
#include "../../SMPP/States/SMPPSessionOpenState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

////////////////////////////////////////////////////////

class CUnbindActionImpl : public IUnbindAction{
public:
	CUnbindActionImpl();
	virtual ~CUnbindActionImpl();

	virtual void Initialize( SP<IPDUUnbind> pdu, SP<ISMPPClient> client );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUUnbind> m_PDUUnbind;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IUnbindAction, CUnbindActionImpl )

////////////////////////////////////////////////////////
CUnbindActionImpl::CUnbindActionImpl(){
}

////////////////////////////////////////////////////////
CUnbindActionImpl::~CUnbindActionImpl(){
}

////////////////////////////////////////////////////////
void 
CUnbindActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CUnbindActionImpl::Initialize( SP<IPDUUnbind> pdu, SP<ISMPPClient> client ){
m_Client = client;
m_PDUUnbind = pdu;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CUnbindActionImpl::Perform( CH<IPDU> pdu ){
/*-90
  CH<ISMPPSessionWaitingUnbindState> okState;
  okState->Initialize( m_Client, m_PDUUnbind->GetSequenceNumber() );

  CH<ISMPPSessionClosedState> failedState;
  failedState->Initialize( m_Client );
  m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionClosedState>( failedState );
*/
//Open! У меня клиент, closed когда будет получен UnbindResp
CH<ISMPPSessionOpenState> okState;
okState->Initialize( m_Client );
//*90  m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionWaitingUnbindState>( okState );
return SafeCastCH<ISMPPSessionState, ISMPPSessionOpenState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CUnbindActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////