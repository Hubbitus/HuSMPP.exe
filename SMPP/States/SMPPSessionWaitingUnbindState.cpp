////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionWaitingUnbindState.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SMPPSessionWaitingUnbindState.h"
#include "../../Common/Actions/UnbindRespAction.h"

/*-52
#include "../../Common/CmnHdr.h"

#include "SMPPSessionWaitingUnbindState.h"
#include "../../Common/Actions/nullaction.h"
#include "../../Common/Actions/UnbindRespAction.h"
*/
////////////////////////////////////////////////////////
class CSMPPSessionWaitingUnbindStateImpl : public ISMPPSessionWaitingUnbindState
{
public:
  //
  CSMPPSessionWaitingUnbindStateImpl();
  virtual ~CSMPPSessionWaitingUnbindStateImpl();

  //
  virtual void Initialize( SP<ISMPPClient> client, DWORD sequenceNumber );

  SMPP_SESSION_STATE_BASICS_DECLARATION

protected:

private:
  // private member functions
  virtual void Initialize();

  // private fields
  DWORD m_SequenceNumber;
  SP<ISMPPClient> m_Client;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionWaitingUnbindStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionWaitingUnbindStateImpl::CSMPPSessionWaitingUnbindStateImpl(){
}

////////////////////////////////////////////////////////
CSMPPSessionWaitingUnbindStateImpl::~CSMPPSessionWaitingUnbindStateImpl()
{
}

////////////////////////////////////////////////////////
void 
CSMPPSessionWaitingUnbindStateImpl::Initialize()
{
}

////////////////////////////////////////////////////////
void
CSMPPSessionWaitingUnbindStateImpl::Initialize(  SP<ISMPPClient> client, DWORD sequenceNumber )
{
  m_SequenceNumber = sequenceNumber;
  m_Client = client;
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUUnknown )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUBindTransceiverResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingUnbindState, CSMPPSessionWaitingUnbindStateImpl, IPDUDataSmResp )

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionWaitingUnbindStateImpl::Process( SP<IPDUUnbindResp> pdu ){
CH<IUnbindRespAction> retVal;
  
  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
    throw CError( "CSMPPSessionWaitingUnbindStateImpl::Process( SP<IPDUUnbindResp> pdu ) - wrong sequence number" );

  retVal->Initialize( pdu, m_Client );
  return ( SafeCastCH<IAction, IUnbindRespAction>( retVal ) );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
