////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionBoundTrxState.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SMPPSessionBoundTrxState.h"
#include "../../Common/Actions/EnquireLinkAction.h"
#include "../../Common/Actions/UnbindAction.h"

#include "../PDU/PDUDeliverSm.h"
#include "../../Common/Actions/ForwardPDUAction.h"

////////////////////////////////////////////////////////

class CSMPPSessionBoundTrxStateImpl : public ISMPPSessionBoundTrxState{
public:
  CSMPPSessionBoundTrxStateImpl();
  virtual ~CSMPPSessionBoundTrxStateImpl();

  virtual void Initialize( SP<ISMPPClient> client );

SMPP_SESSION_STATE_BASICS_DECLARATION

private:
	virtual void Initialize();

	SP<ISMPPClient> m_Client;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionBoundTrxStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionBoundTrxStateImpl::CSMPPSessionBoundTrxStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionBoundTrxStateImpl::~CSMPPSessionBoundTrxStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionBoundTrxStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
void
CSMPPSessionBoundTrxStateImpl::Initialize( SP<ISMPPClient> client ){
m_Client = client;
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUUnknown )
//+91+4
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindReceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindTransmitter )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUDataSmResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionBoundTrxState, CSMPPSessionBoundTrxStateImpl, IPDUCache )

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUEnquireLink> pdu ){
CH<IEnquireLinkAction> retVal;
//-53  retVal->Initialize( m_Client, ( IPDUEnquireLink* ) pdu );
retVal->Initialize( m_Client, (IPDU *) ( IPDUEnquireLink* ) pdu );

return ( SafeCastCH<IAction, IEnquireLinkAction>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUUnbind> pdu ){
CH<IUnbindAction> retVal;
retVal->Initialize( pdu, m_Client );

return ( SafeCastCH<IAction, IUnbindAction>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUDeliverSm> pdu ){
//-13  string msg = "CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUDeliverSm> pdu ): ";
//-13  msg += pdu->GetShortMessage();
//-13  GETLOG->LogMessage( LOGFILENAME, msg.c_str() );

CH<IForwardPDUAction> retVal;
//-53  retVal->Initialize( m_Client, ( IPDUDeliverSm* ) pdu );
retVal->Initialize( m_Client, ( IPDU * )( IPDUDeliverSm* ) pdu );

return ( SafeCastCH<IAction, IForwardPDUAction>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUSubmitSmResp> pdu ){
//-13  string msg = "CSMPPSessionBoundTrxStateImpl::Process( SP<IPDUSubmitSmResp> pdu ): ";
//-13  GETLOG->LogMessage( LOGFILENAME, msg.c_str() );
//-13  m_Client->GetNAT()->MakeSequenceNumberBackwardTranslation( ( IPDUSubmitSmResp* ) pdu );

CH<IForwardPDUAction> retVal;
//-53  retVal->Initialize( m_Client, ( IPDUSubmitSmResp* ) pdu );
retVal->Initialize( m_Client, ( IPDU * )( IPDUSubmitSmResp* ) pdu );

return ( SafeCastCH<IAction, IForwardPDUAction>( retVal ) );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////