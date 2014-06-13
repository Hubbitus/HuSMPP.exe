////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : bindtransceiveraction.cpp
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bindtransceiveraction.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"

//*90 #include "../../SMPP/States/SMPPSessionWaitingBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionOpenState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

////////////////////////////////////////////////////////

class CBindTransceiverActionImpl : public IBindTransceiverAction{
public:
	CBindTransceiverActionImpl();
	virtual ~CBindTransceiverActionImpl();

	virtual void Initialize( SP<IPDUBindTransceiver> pdu, SP<ISMPPClient> client );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindTransceiver> m_PDUBindTransceiver;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindTransceiverAction, CBindTransceiverActionImpl )

////////////////////////////////////////////////////////
CBindTransceiverActionImpl::CBindTransceiverActionImpl(){
}

////////////////////////////////////////////////////////
CBindTransceiverActionImpl::~CBindTransceiverActionImpl(){
}

////////////////////////////////////////////////////////
void 
CBindTransceiverActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindTransceiverActionImpl::Initialize( SP<IPDUBindTransceiver> pdu, SP<ISMPPClient> client ){
m_Client = client;
m_PDUBindTransceiver = pdu;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindTransceiverActionImpl::Perform( CH<IPDU> pdu ){
//*90 CH<ISMPPSessionWaitingBoundTrxState> okState;
CH<ISMPPSessionOpenState> okState;
//*90okState->Initialize( m_Client, m_PDUBindTransceiver->GetSequenceNumber() );
okState->Initialize( m_Client );

//*90 m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionWaitingBoundTrxState>( okState );
return SafeCastCH<ISMPPSessionState, ISMPPSessionOpenState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindTransceiverActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////