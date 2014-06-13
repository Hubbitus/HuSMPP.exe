////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: BindReceiverRespAction.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../CmnHdr.h"

#include "BindReceiverRespAction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/States/SMPPSessionBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

#include "../../SMPP/PDU.h"
#include "../../SMPP/PDU/PDUBindReceiver.h"

#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////

class CBindReceiverRespActionImpl : public IBindReceiverRespAction{
public:
	CBindReceiverRespActionImpl();
	virtual ~CBindReceiverRespActionImpl();

	virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindReceiverResp> pdu );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindReceiverResp> m_PDUBindReceiverResp;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindReceiverRespAction, CBindReceiverRespActionImpl )

////////////////////////////////////////////////////////
CBindReceiverRespActionImpl::CBindReceiverRespActionImpl(){
}

////////////////////////////////////////////////////////
CBindReceiverRespActionImpl::~CBindReceiverRespActionImpl(){
}

////////////////////////////////////////////////////////
void 
CBindReceiverRespActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindReceiverRespActionImpl::Initialize( SP<ISMPPClient> client, SP<IPDUBindReceiverResp> pdu ){
m_PDUBindReceiverResp = pdu;
m_Client = client;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindReceiverRespActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionBoundTrxState> okState;
okState->Initialize( m_Client );

return SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindReceiverRespActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////