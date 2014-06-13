////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindTransmitterRespAction.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BindTransmitterAction.h"

#include "../../SMPP/SMPPSessionState.h"
#include "Action.h"

//*90 #include "../../SMPP/States/SMPPSessionWaitingBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionOpenState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

////////////////////////////////////////////////////////

class CBindTransmitterActionImpl : public IBindTransmitterAction{
public:
	CBindTransmitterActionImpl();
	virtual ~CBindTransmitterActionImpl();

	virtual void Initialize( SP<IPDUBindTransmitter> pdu, SP<ISMPPClient> client );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindTransmitter> m_PDUBindTransmitter;
	SP<ISMPPClient> m_Client;

	CH<ISMPPSessionState> m_NewState;
	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindTransmitterAction, CBindTransmitterActionImpl )

////////////////////////////////////////////////////////
CBindTransmitterActionImpl::CBindTransmitterActionImpl(){
}

////////////////////////////////////////////////////////
CBindTransmitterActionImpl::~CBindTransmitterActionImpl(){
}

////////////////////////////////////////////////////////
void 
CBindTransmitterActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindTransmitterActionImpl::Initialize( SP<IPDUBindTransmitter> pdu, SP<ISMPPClient> client ){
m_Client = client;
m_PDUBindTransmitter = pdu;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindTransmitterActionImpl::Perform( CH<IPDU> pdu ){
//*90 CH<ISMPPSessionWaitingBoundTrxState> okState;
CH<ISMPPSessionOpenState> okState;
//*90okState->Initialize( m_Client, m_PDUBindTransmitter->GetSequenceNumber() );
okState->Initialize( m_Client );

//*90 m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionWaitingBoundTrxState>( okState );
m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionOpenState>( okState );

return m_NewState;
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindTransmitterActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////