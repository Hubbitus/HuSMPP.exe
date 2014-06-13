////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionClosedState.cpp
// Modifyed: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../Common/CmnHdr.h"

#include "SMPPSessionClosedState.h"
#include "../../Common/Actions/NullAction.h"
#include "../../Common/Actions/CompositeAction.h"
#include "../../Common/Actions/BindTransceiverAction.h"
//+91+2
#include "../../Common/Actions/BindReceiverAction.h"
#include "../../Common/Actions/BindTransmitterAction.h"

////////////////////////////////////////////////////////

class CSMPPSessionClosedStateImpl : public ISMPPSessionClosedState{
public:
	CSMPPSessionClosedStateImpl();
	virtual ~CSMPPSessionClosedStateImpl();

	virtual void Initialize( SP<ISMPPClient> client );

SMPP_SESSION_STATE_BASICS_DECLARATION

private:
	virtual void Initialize();

	SP<ISMPPClient> m_Client;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionClosedStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionClosedStateImpl::CSMPPSessionClosedStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionClosedStateImpl::~CSMPPSessionClosedStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionClosedStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionClosedStateImpl::Initialize( SP<ISMPPClient> client ){
m_Client = client;
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUUnknown )
//+91+2
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUDataSmResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionClosedState, CSMPPSessionClosedStateImpl, IPDUCache )

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionClosedStateImpl::Process( SP<IPDUBindTransceiver> pdu ){
CH<IBindTransceiverAction> retVal;
retVal->Initialize( pdu, m_Client );
return ( SafeCastCH<IAction, IBindTransceiverAction>( retVal ) );
}

////////////////////////////////////////////////////////
//+91
CH<IAction>
CSMPPSessionClosedStateImpl::Process( SP<IPDUBindReceiver> pdu ){
  CH<IBindReceiverAction> retVal;
  retVal->Initialize( pdu, m_Client );
  return ( SafeCastCH<IAction, IBindReceiverAction>( retVal ) );
}

////////////////////////////////////////////////////////
//+91
CH<IAction>
CSMPPSessionClosedStateImpl::Process( SP<IPDUBindTransmitter> pdu ){
  CH<IBindTransmitterAction> retVal;
  retVal->Initialize( pdu, m_Client );
  return ( SafeCastCH<IAction, IBindTransmitterAction>( retVal ) );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////