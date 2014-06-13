////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindTransmitterResp.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransmitterResp.h"
#include "../../Common/ubstr.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUBindTransmitterRespImpl : public IPDUBindTransmitterResp{
public:
	CPDUBindTransmitterRespImpl();
	virtual ~CPDUBindTransmitterRespImpl();

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
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransmitterResp, CPDUBindTransmitterRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUBindTransmitterRespImpl )

////////////////////////////////////////////////////////
CPDUBindTransmitterRespImpl::CPDUBindTransmitterRespImpl(){
m_SystemId = "";
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_BIND_TRANSMITTER_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUBindTransmitterRespImpl::~CPDUBindTransmitterRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUBindTransmitterRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
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
CPDUBindTransmitterRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUBindTransmitterRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUBindTransmitterRespImpl::GetRawData(){
CH<IRawBuffer> retVal;
m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_SystemId.length() + 1;

m_Header.command_id = PDU_BIND_TRANSMITTER_RESP_ID;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_SystemId.c_str() ), ( int )m_SystemId.length() + 1 );

m_Header.NTOH();

return retVal;
}

////////////////////////////////////////////////////////
void
CPDUBindTransmitterRespImpl::SetSystemId( const char* system_id ){
m_SystemId = SAFESTR( system_id );
}

////////////////////////////////////////////////////////
const string&
CPDUBindTransmitterRespImpl::GetSystemId(){
return m_SystemId;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////