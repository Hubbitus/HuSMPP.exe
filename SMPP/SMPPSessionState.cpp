////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionState.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-19 //91.1
//		Ad process of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMPPSessionState.h"

////////////////////////////////////////////////////////

class CSMPPSessionStateImpl : public ISMPPSessionState{
public:
	CSMPPSessionStateImpl();
	virtual ~CSMPPSessionStateImpl();

	virtual void Initialize();

SMPP_SESSION_STATE_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionState, CSMPPSessionStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionStateImpl::CSMPPSessionStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionStateImpl::~CSMPPSessionStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUUnknown )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindTransceiverResp )
//+90+4
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindReceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindTransmitter )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUDataSmResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionState, CSMPPSessionStateImpl, IPDUCache )
// =================== END OF FILE =====================
////////////////////////////////////////////////////////