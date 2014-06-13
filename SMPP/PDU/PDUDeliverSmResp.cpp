////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmResp.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDeliverSmResp.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUDeliverSmRespImpl : public IPDUDeliverSmResp{
public:
	CPDUDeliverSmRespImpl();
	virtual ~CPDUDeliverSmRespImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

private:
	BYTE m_MessageId;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDeliverSmResp, CPDUDeliverSmRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUDeliverSmRespImpl )

////////////////////////////////////////////////////////
CPDUDeliverSmRespImpl::CPDUDeliverSmRespImpl(){
m_MessageId = 0;
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_DELIVER_SM_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUDeliverSmRespImpl::~CPDUDeliverSmRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUDeliverSmRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
unsigned int offset = 0;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();
offset += sizeof( m_Header );
chASSERT( offset <= m_Header.command_length );
rawBuffer->Skip( sizeof( m_Header ) );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUDeliverSmRespImpl::GetRawData(){
CH<IRawBuffer> retVal;

m_Header.command_length = sizeof( m_Header );
m_Header.command_length += 1; // message_id

m_Header.command_id = PDU_DELIVER_SM_RESP_ID;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( &m_MessageId ), sizeof( m_MessageId ) );

m_Header.NTOH();

return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////