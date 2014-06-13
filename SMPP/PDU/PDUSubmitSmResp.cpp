////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmResp.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUSubmitSmResp.h"
#include "../SMPPSessionState.h"
#include "../../Common/ubstr.h"

////////////////////////////////////////////////////////

class CPDUSubmitSmRespImpl : public IPDUSubmitSmResp{
public:
	CPDUSubmitSmRespImpl();
	virtual ~CPDUSubmitSmRespImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

	virtual void SetMessageId( const char* message_id );
	virtual const std::string& GetMessageId();

private:
	std::string m_MessageId;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUSubmitSmResp, CPDUSubmitSmRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUSubmitSmRespImpl )

////////////////////////////////////////////////////////
CPDUSubmitSmRespImpl::CPDUSubmitSmRespImpl(){
m_MessageId = "";
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_SUBMIT_SM_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUSubmitSmRespImpl::~CPDUSubmitSmRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUSubmitSmRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
unsigned int offset = 0;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();
offset += sizeof( m_Header );
chASSERT( offset <= m_Header.command_length );
rawBuffer->Skip( sizeof( m_Header ) );

	if ( IsOnlyHeader() ) return;

m_MessageId = rawBuffer->GetCString( 65 );
offset += ( unsigned int ) m_MessageId.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_OptionalParams->Initialize( rawBuffer );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUSubmitSmRespImpl::GetRawData(){
CH<IRawBuffer> retVal;

m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_MessageId.length() + 1;

m_Header.command_id = PDU_SUBMIT_SM_RESP_ID;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_MessageId.c_str() ), ( int ) m_MessageId.length() + 1 );

m_Header.NTOH();

return retVal;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmRespImpl::SetMessageId( const char* message_id ){
m_MessageId = SAFESTR( message_id );
}

////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmRespImpl::GetMessageId(){
return m_MessageId;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////