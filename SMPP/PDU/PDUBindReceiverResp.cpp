////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindReceiverResp.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindReceiverResp.h"
#include "../../Common/ubstr.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUBindReceiverRespImpl : public IPDUBindReceiverResp{
public:
	CPDUBindReceiverRespImpl();
	virtual ~CPDUBindReceiverRespImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

	virtual void SetSystemId( const char* system_id );
	virtual const std::string& GetSystemId();

private:
	std::string m_SystemId;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindReceiverResp, CPDUBindReceiverRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUBindReceiverRespImpl )

////////////////////////////////////////////////////////
CPDUBindReceiverRespImpl::CPDUBindReceiverRespImpl(){
m_SystemId = "";
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_BIND_RECEIVER_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUBindReceiverRespImpl::~CPDUBindReceiverRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUBindReceiverRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
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
CPDUBindReceiverRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUBindReceiverRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUBindReceiverRespImpl::GetRawData(){
CH<IRawBuffer> retVal;
m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_SystemId.length() + 1;

m_Header.command_id = PDU_BIND_RECEIVER_RESP_ID;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_SystemId.c_str() ), ( int )m_SystemId.length() + 1 );

m_Header.NTOH();

return retVal;
}

////////////////////////////////////////////////////////
void
CPDUBindReceiverRespImpl::SetSystemId( const char* system_id ){
m_SystemId = SAFESTR( system_id );
}

////////////////////////////////////////////////////////
const std::string&
CPDUBindReceiverRespImpl::GetSystemId(){
return m_SystemId;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////