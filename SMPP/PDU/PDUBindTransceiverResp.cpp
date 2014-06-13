////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiverResp.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransceiverResp.h"
#include "../../Common/ubstr.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUBindTransceiverRespImpl : public IPDUBindTransceiverResp{
public:
	CPDUBindTransceiverRespImpl();
	virtual ~CPDUBindTransceiverRespImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

	virtual void SetSystemId( const char* system_id );
	virtual const string& GetSystemId();

private:
	string m_SystemId;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransceiverResp, CPDUBindTransceiverRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUBindTransceiverRespImpl )

////////////////////////////////////////////////////////
CPDUBindTransceiverRespImpl::CPDUBindTransceiverRespImpl(){
m_SystemId = "";
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_BIND_TRANSCEIVER_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUBindTransceiverRespImpl::~CPDUBindTransceiverRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
unsigned int offset = 0;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();
offset += sizeof( m_Header );
chASSERT( offset <= m_Header.command_length );
rawBuffer->Skip( sizeof( m_Header ) );

m_SystemId = rawBuffer->GetCString( 16 );
offset += ( unsigned int ) m_SystemId.length() + 1;
//chASSERT( offset <= m_Header.command_length );

m_OptionalParams->Initialize( rawBuffer );
}

////////////////////////////////////////////////////////
void
CPDUBindTransceiverRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUBindTransceiverRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUBindTransceiverRespImpl::GetRawData(){
CH<IRawBuffer> retVal;
m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_SystemId.length() + 1;

m_Header.command_id = PDU_BIND_TRANSCEIVER_RESP_ID;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_SystemId.c_str() ), ( int )m_SystemId.length() + 1 );

m_Header.NTOH();

return retVal;
}

////////////////////////////////////////////////////////
void
CPDUBindTransceiverRespImpl::SetSystemId( const char* system_id ){
m_SystemId = SAFESTR( system_id );
}

////////////////////////////////////////////////////////
const string&
CPDUBindTransceiverRespImpl::GetSystemId(){
return m_SystemId;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////