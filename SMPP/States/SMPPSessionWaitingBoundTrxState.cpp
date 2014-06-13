////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionWaitingBoundTrxState.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SMPPSessionWaitingBoundTrxState.h"
#include "../../Common/Actions/bindtransceiverrespaction.h"
#include "../../HuSMPP.h"
#include "../PDU/PDUBindTransceiverResp.h"

/*-52
#include "../../Common/CmnHdr.h"

#include "SMPPSessionWaitingBoundTrxState.h"
#include "../../Common/Actions/nullaction.h"
#include "../../Common/Actions/bindtransceiverrespaction.h"
*/
////////////////////////////////////////////////////////
class CSMPPSessionWaitingBoundTrxStateImpl : public ISMPPSessionWaitingBoundTrxState
{
public:
  //
  CSMPPSessionWaitingBoundTrxStateImpl();
  virtual ~CSMPPSessionWaitingBoundTrxStateImpl();

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
IMPLEMENT_CH_REFCOUNTING( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl )

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_BASICS_DEFINITION( CSMPPSessionWaitingBoundTrxStateImpl )

////////////////////////////////////////////////////////
CSMPPSessionWaitingBoundTrxStateImpl::CSMPPSessionWaitingBoundTrxStateImpl()
{
}

////////////////////////////////////////////////////////
CSMPPSessionWaitingBoundTrxStateImpl::~CSMPPSessionWaitingBoundTrxStateImpl()
{
}

////////////////////////////////////////////////////////
void 
CSMPPSessionWaitingBoundTrxStateImpl::Initialize()
{
}

////////////////////////////////////////////////////////
void
CSMPPSessionWaitingBoundTrxStateImpl::Initialize(  SP<ISMPPClient> client, DWORD sequenceNumber )
{
  m_SequenceNumber = sequenceNumber;
  m_Client = client;
}

////////////////////////////////////////////////////////
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUUnknown )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUBindTransceiver )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUEnquireLink )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUEnquireLinkResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUGenericNack )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUOutbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUUnbind )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUUnbindResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUSubmitSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUSubmitSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUDeliverSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUDeliverSmResp )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUDataSm )
SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( ISMPPSessionWaitingBoundTrxState, CSMPPSessionWaitingBoundTrxStateImpl, IPDUDataSmResp )

////////////////////////////////////////////////////////
CH<IAction>
CSMPPSessionWaitingBoundTrxStateImpl::Process( SP<IPDUBindTransceiverResp> pdu )
{
  CH<IBindTransceiverRespAction> retVal;
  
  if ( pdu->GetSequenceNumber() != m_SequenceNumber )
    throw CError( "CSMPPSessionWaitingBoundTrxStateImpl::Process( SP<IPDUBindTransceiverResp> pdu ) - wrong sequence number" );

  retVal->Initialize( m_Client, pdu );
  return ( SafeCastCH<IAction, IBindTransceiverRespAction>( retVal ) );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
