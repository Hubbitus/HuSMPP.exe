////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : UnbindRespAction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../Common/CmnHdr.h"

#include "../../Common/Actions/UnbindRespAction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

#include "../../SMPP/PDU.h"
#include "../../SMPP/PDU/PDUUnbindResp.h"

#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////

class CUnbindRespActionImpl : public IUnbindRespAction{
public:
	CUnbindRespActionImpl();
	virtual ~CUnbindRespActionImpl();

	virtual void Initialize( SP<IPDUUnbindResp> pdu, SP<ISMPPClient> client );

	virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
	virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDUUnbindResp> m_PDUUnbindResp;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IUnbindRespAction, CUnbindRespActionImpl )

////////////////////////////////////////////////////////
CUnbindRespActionImpl::CUnbindRespActionImpl(){
}

////////////////////////////////////////////////////////
CUnbindRespActionImpl::~CUnbindRespActionImpl(){
}

////////////////////////////////////////////////////////
void 
CUnbindRespActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CUnbindRespActionImpl::Initialize( SP<IPDUUnbindResp> pdu, SP<ISMPPClient> client ){
m_Client = client;
m_PDUUnbindResp = pdu;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CUnbindRespActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionClosedState> okState;
okState->Initialize( m_Client );
return SafeCastCH<ISMPPSessionState, ISMPPSessionClosedState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CUnbindRespActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////