////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindReceiverAction.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bindReceiveraction.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

#include "../../SMPP/States/SMPPSessionOpenState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

////////////////////////////////////////////////////////

class CBindReceiverActionImpl : public IBindReceiverAction{
public:
	CBindReceiverActionImpl();
	virtual ~CBindReceiverActionImpl();

	virtual void Initialize( SP<IPDUBindReceiver> pdu, SP<ISMPPClient> client );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindReceiver> m_PDUBindReceiver;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindReceiverAction, CBindReceiverActionImpl )

////////////////////////////////////////////////////////
CBindReceiverActionImpl::CBindReceiverActionImpl(){
}

////////////////////////////////////////////////////////
CBindReceiverActionImpl::~CBindReceiverActionImpl(){
}

////////////////////////////////////////////////////////
void 
CBindReceiverActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindReceiverActionImpl::Initialize( SP<IPDUBindReceiver> pdu, SP<ISMPPClient> client ){
m_Client = client;
m_PDUBindReceiver = pdu;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindReceiverActionImpl::Perform( CH<IPDU> pdu ){
//*90 CH<ISMPPSessionWaitingBoundTrxState> okState;
CH<ISMPPSessionOpenState> okState;
//*90okState->Initialize( m_Client, m_PDUBindReceiver->GetSequenceNumber() );
okState->Initialize( m_Client );

//*90 m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionWaitingBoundTrxState>( okState );
return SafeCastCH<ISMPPSessionState, ISMPPSessionOpenState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindReceiverActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////