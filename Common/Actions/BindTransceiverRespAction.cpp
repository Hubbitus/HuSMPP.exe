////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : bindtransceiverrespaction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../CmnHdr.h"

#include "bindtransceiverrespaction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/States/SMPPSessionBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

#include "../../SMPP/PDU.h"
#include "../../SMPP/PDU/PDUBindTransceiver.h"

#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////

class CBindTransceiverRespActionImpl : public IBindTransceiverRespAction{
public:
	CBindTransceiverRespActionImpl();
	virtual ~CBindTransceiverRespActionImpl();

	virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindTransceiverResp> pdu );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindTransceiverResp> m_PDUBindTransceiverResp;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindTransceiverRespAction, CBindTransceiverRespActionImpl )

////////////////////////////////////////////////////////
CBindTransceiverRespActionImpl::CBindTransceiverRespActionImpl(){
}

////////////////////////////////////////////////////////
CBindTransceiverRespActionImpl::~CBindTransceiverRespActionImpl(){
}

////////////////////////////////////////////////////////
void 
CBindTransceiverRespActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindTransceiverRespActionImpl::Initialize( SP<ISMPPClient> client, SP<IPDUBindTransceiverResp> pdu ){
m_PDUBindTransceiverResp = pdu;
m_Client = client;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindTransceiverRespActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionBoundTrxState> okState;
okState->Initialize( m_Client );

return SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindTransceiverRespActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////