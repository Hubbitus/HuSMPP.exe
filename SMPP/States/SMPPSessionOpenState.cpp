////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMPPSessionOpenState.cpp
// Added by: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../Common/CmnHdr.h"

#include "SMPPSessionOpenState.h"
#include "../../Common/Actions/NullAction.h"
#include "../../Common/Actions/CompositeAction.h"
#include "../../Common/Actions/BindTransceiverAction.h"
#include "../../Common/Actions/BindTransceiverRespAction.h"
#include "../../Common/Actions/BindReceiverAction.h"
#include "../../Common/Actions/BindReceiverRespAction.h"
#include "../../Common/Actions/BindTransmitterAction.h"
#include "../../Common/Actions/BindTransmitterRespAction.h"

////////////////////////////////////////////////////////

class CSMPPSessionOpenStateImpl : public ISMPPSessionOpenState{
public:
	CSMPPSessionOpenStateImpl();
	virtual ~CSMPPSessionOpenStateImpl();

	virtual void Initialize( SP<ISMPPClient> client );

SMPP_SESSION_STATE_BASICS_DECLARATION

private:
	virtual void Initialize();

	SP<ISMPPClient> m_Client;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionOpenStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionOpenStateImpl::CSMPPSessionOpenStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionOpenStateImpl::~CSMPPSessionOpenStateImpl(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionOpenStateImpl::Initialize(){
}

////////////////////////////////////////////////////////
void 
CSMPPSessionOpenStateImpl::Initialize( SP<ISMPPClient> client ){
m_Client = client;
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUUnknown )
//?SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUDataSmResp )

/*91 TODO Позже хорошо бы с ними разобраться, и вынести все действия в Actions, вместо того, чтобы делать
их OnPDUEventHandler*'ах!
*/
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindReceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindReceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindTransmitter )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindTransmitterResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUBindTransceiverResp )
//+91.1
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionOpenState, CSMPPSessionOpenStateImpl, IPDUCache )
/*?91
////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionOpenStateImpl::Process( SP<IPDUBindTransceiverResp> pdu ){
  CH<IBindTransceiverRespAction> retVal;
  
//?  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
//?    throw CError( "CSMPPSessionOpenStateImpl::Process( SP<IPDUBindTransceiverResp> pdu ) - wrong sequence number" );

  retVal->Initialize( m_Client, pdu );
  return ( SafeCastCH<IAction, IBindTransceiverRespAction>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionOpenStateImpl::Process( SP<IPDUBindReceiverResp> pdu )
{
  CH<IBindReceiverRespAction> retVal;
  
//?  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
//?    throw CError( "CSMPPSessionOpenStateImpl::Process( SP<IPDUBindReceiverResp> pdu ) - wrong sequence number" );

  retVal->Initialize( m_Client, pdu );
  return ( SafeCastCH<IAction, IPDUBindReceiverResp>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionOpenStateImpl::Process( SP<IPDUBindTransmitterResp> pdu )
{
  CH<IBindTransmitterRespAction> retVal;
  
//?  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
//?    throw CError( "CSMPPSessionOpenStateImpl::Process( SP<IPDUBindTransmitterResp> pdu ) - wrong sequence number" );

  retVal->Initialize( m_Client, pdu );
  return ( SafeCastCH<IAction, IPDUBindTransmitterResp>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionOpenStateImpl::Process( SP<IPDUUnbindResp> pdu ){
CH<IUnbindRespAction> retVal;
  
//?  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
//?    throw CError( "CSMPPSessionWaitingUnbindStateImpl::Process( SP<IPDUUnbindResp> pdu ) - wrong sequence number" );

  retVal->Initialize( pdu, m_Client );
  return ( SafeCastCH<IAction, IUnbindRespAction>( retVal ) );
}
*/
// =================== END OF FILE =====================
////////////////////////////////////////////////////////