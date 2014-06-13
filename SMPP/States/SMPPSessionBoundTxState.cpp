////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundTxState.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../Common/CmnHdr.h"

#include "SMPPSessionBoundTxState.h"
#include "../../Common/Actions/nullaction.h"

////////////////////////////////////////////////////////

class CSMPPSessionBoundTxStateImpl : public ISMPPSessionBoundTxState{
public:
	CSMPPSessionBoundTxStateImpl();
	virtual ~CSMPPSessionBoundTxStateImpl();

	virtual void Initialize();

SMPP_SESSION_STATE_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionBoundTxStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionBoundTxStateImpl::CSMPPSessionBoundTxStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionBoundTxStateImpl::~CSMPPSessionBoundTxStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionBoundTxStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUUnknown )
//+91+4
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindReceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindTransmitter )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUDataSmResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTxState, CSMPPSessionBoundTxStateImpl, IPDUCache )
// =================== END OF FILE =====================
////////////////////////////////////////////////////////