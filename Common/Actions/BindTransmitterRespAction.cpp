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

#include "../CmnHdr.h"

#include "BindTransmitterRespAction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/States/SMPPSessionBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

#include "../../SMPP/PDU.h"
#include "../../SMPP/PDU/PDUBindTransmitter.h"

#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////

class CBindTransmitterRespActionImpl : public IBindTransmitterRespAction{
public:
	CBindTransmitterRespActionImpl();
	virtual ~CBindTransmitterRespActionImpl();

	virtual void Initialize( SP<ISMPPClient> client, SP<IPDUBindTransmitterResp> pdu );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUBindTransmitterResp> m_PDUBindTransmitterResp;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IBindTransmitterRespAction, CBindTransmitterRespActionImpl )

////////////////////////////////////////////////////////
CBindTransmitterRespActionImpl::CBindTransmitterRespActionImpl(){
}

////////////////////////////////////////////////////////
CBindTransmitterRespActionImpl::~CBindTransmitterRespActionImpl(){
}

////////////////////////////////////////////////////////
void
CBindTransmitterRespActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CBindTransmitterRespActionImpl::Initialize( SP<ISMPPClient> client, SP<IPDUBindTransmitterResp> pdu ){
m_PDUBindTransmitterResp = pdu;
m_Client = client;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CBindTransmitterRespActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionBoundTrxState> okState;
okState->Initialize( m_Client );

return SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CBindTransmitterRespActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////