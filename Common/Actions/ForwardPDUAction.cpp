////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : ForwardPDUAction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../CmnHdr.h"

#include "ForwardPDUAction.h"
#include "../../SMPP/SMPPSessionState.h"
#include "../../SMPP/States/SMPPSessionBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

#include "../../SMPP/PDU.h"

#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////

class CForwardPDUActionImpl : public IForwardPDUAction{
public:
  CForwardPDUActionImpl();
  virtual ~CForwardPDUActionImpl();

  virtual void Initialize( SP<ISMPPClient> client, SP<IPDU> pdu );

  virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
  virtual CH<IPDU> GetResponse();

private:
	virtual void Initialize();

	SP<IPDU> m_PDU;
	SP<ISMPPClient> m_Client;

	CH<IPDU> m_PDUResponse;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IForwardPDUAction, CForwardPDUActionImpl )

////////////////////////////////////////////////////////
CForwardPDUActionImpl::CForwardPDUActionImpl(){
}

////////////////////////////////////////////////////////
CForwardPDUActionImpl::~CForwardPDUActionImpl(){
}

////////////////////////////////////////////////////////
void 
CForwardPDUActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void
CForwardPDUActionImpl::Initialize( SP<ISMPPClient> client, SP<IPDU> pdu ){
m_PDU = pdu;
m_Client = client;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CForwardPDUActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionBoundTrxState> okState;
okState->Initialize( m_Client );

//-10  m_Client->GetInboundClientFilter()->AddPDU( pdu );
//-10m_Client->GetInboundClientFilter()->GetOutPin()->TransmitData();

return SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );
}

////////////////////////////////////////////////////////
CH<IPDU>
CForwardPDUActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////