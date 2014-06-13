////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundRxState.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../Common/CmnHdr.h"

#include "SMPPSessionBoundRxState.h"
#include "../../Common/Actions/nullaction.h"

////////////////////////////////////////////////////////

class CSMPPSessionBoundRxStateImpl : public ISMPPSessionBoundRxState{
public:
	CSMPPSessionBoundRxStateImpl();
	virtual ~CSMPPSessionBoundRxStateImpl();

	virtual void Initialize();

SMPP_SESSION_STATE_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionBoundRxStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionBoundRxStateImpl::CSMPPSessionBoundRxStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionBoundRxStateImpl::~CSMPPSessionBoundRxStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionBoundRxStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUUnknown )
//+91+4
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindReceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindTransmitter )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUDataSmResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundRxState, CSMPPSessionBoundRxStateImpl, IPDUCache )
// =================== END OF FILE =====================
////////////////////////////////////////////////////////