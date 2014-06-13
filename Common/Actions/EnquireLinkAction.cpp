////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : EnquireLinkAction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "EnquireLinkAction.h"

#include "../../SMPP/States/SMPPSessionBoundTrxState.h"
#include "../../SMPP/States/SMPPSessionClosedState.h"

////////////////////////////////////////////////////////

class CEnquireLinkActionImpl : public IEnquireLinkAction{
public:
	CEnquireLinkActionImpl();
	virtual ~CEnquireLinkActionImpl();

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
IMPLEMENT_CH_REFCOUNTING( IEnquireLinkAction, CEnquireLinkActionImpl )

////////////////////////////////////////////////////////
CEnquireLinkActionImpl::CEnquireLinkActionImpl(){
}

////////////////////////////////////////////////////////
CEnquireLinkActionImpl::~CEnquireLinkActionImpl(){
}

////////////////////////////////////////////////////////
void 
CEnquireLinkActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
void
CEnquireLinkActionImpl::Initialize( SP<ISMPPClient> client, SP<IPDU> pdu ){
m_PDU = pdu;
m_Client = client;
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CEnquireLinkActionImpl::Perform( CH<IPDU> pdu ){
CH<ISMPPSessionBoundTrxState> okState;
okState->Initialize( m_Client );
//-62 Остального не надо! А только эту строку вынесем!
return SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );
/*62
  CH<ISMPPSessionClosedState> failedState;
  failedState->Initialize( m_Client );

  m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionClosedState>( failedState );


  CH<IPDUEnquireLinkResp> resp;
  resp->SetSequenceNumber( m_PDU->GetSequenceNumber() );

  m_NewState = SafeCastCH<ISMPPSessionState, ISMPPSessionBoundTrxState>( okState );

  m_PDUResponse = SafeCastCH<IPDU, IPDUEnquireLinkResp>( resp );
  m_Client->GetClientSocket()->Write( m_PDUResponse->GetRawData() );
*/
//-51.2  m_Client->GetClientSocket()->Send( (IPDU*)resp );
}

////////////////////////////////////////////////////////
CH<IPDU>
CEnquireLinkActionImpl::GetResponse(){
return m_PDUResponse;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////