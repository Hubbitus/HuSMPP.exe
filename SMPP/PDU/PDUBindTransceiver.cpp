////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiver.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransceiver.h"
#include "../../Common/ubstr.h"

#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUBindTransceiverImpl : public IPDUBindTransceiver{
public:
	CPDUBindTransceiverImpl();
	virtual ~CPDUBindTransceiverImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

	virtual void SetSystemId( const char* system_id );
	virtual void SetPassword( const char* password );
	virtual void SetSystemType( const char* system_type );

	virtual void SetInterfaceVersion( BYTE interface_version );
	virtual void SetAddrTon( BYTE addr_ton );
	virtual void SetAddrNpi( BYTE addr_npi );
	virtual void SetAddressRange( const char* address_range );

	virtual const string& GetSystemId();
	virtual const string& GetPassword();
	virtual const string& GetSystemType();

	virtual BYTE GetInterfaceVersion();
	virtual BYTE GetAddrTon();
	virtual BYTE GetAddrNpi();
	virtual const string& GetAddressRange();

private:
	string m_SystemId;
	string m_Password;
	string m_SystemType;

	BYTE m_InterfaceVersion;
	BYTE m_AddrTon;
	BYTE m_AddrNpi;
	string m_AddressRange;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransceiver, CPDUBindTransceiverImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUBindTransceiverImpl )

////////////////////////////////////////////////////////
CPDUBindTransceiverImpl::CPDUBindTransceiverImpl(){
m_SystemId = "";
m_Password = "";
m_SystemType = "";

m_InterfaceVersion = PDU_DEFAULT_VERSION;
m_AddrTon = 0;
m_AddrNpi = 0;
m_AddressRange = "";

m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_BIND_TRANSCEIVER_ID;
}

////////////////////////////////////////////////////////
CPDUBindTransceiverImpl::~CPDUBindTransceiverImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
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
chASSERT( offset <= m_Header.command_length );

m_Password = rawBuffer->GetCString( 9 );
offset += ( unsigned int ) m_Password.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_SystemType = rawBuffer->GetCString( 13 );
offset += ( unsigned int ) m_SystemType.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_InterfaceVersion = rawBuffer->GetBYTE();
offset += sizeof( m_InterfaceVersion );
chASSERT( offset <= m_Header.command_length );

m_AddrTon = rawBuffer->GetBYTE();
offset += sizeof( m_AddrTon );
chASSERT( offset <= m_Header.command_length );

m_AddrNpi = rawBuffer->GetBYTE();
offset += sizeof( m_AddrNpi );
chASSERT( offset <= m_Header.command_length );

m_AddressRange = rawBuffer->GetCString( 41 );
offset += ( unsigned int ) m_AddressRange.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_OptionalParams->Initialize( rawBuffer );
}

////////////////////////////////////////////////////////
void
CPDUBindTransceiverImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUBindTransceiverImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUBindTransceiverImpl::GetRawData(){
CH<IRawBuffer> retVal;
m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_SystemId.length() + 1;
m_Header.command_length += ( DWORD ) m_Password.length() + 1;
m_Header.command_length += ( DWORD ) m_SystemType.length() + 1;

m_Header.command_length += 1; // inteface_type
m_Header.command_length += 1; // addr_ton
m_Header.command_length += 1; // addr_npi
m_Header.command_length += ( DWORD ) m_AddressRange.length() + 1;

//-47
m_Header.command_length += m_OptionalParams->GetRawLength(); // OptionalParameters

m_Header.command_id = PDU_BIND_TRANSCEIVER_ID;
m_Header.command_status = ESME_ROK;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_SystemId.c_str() ), ( int )m_SystemId.length() + 1 );
retVal->AddData( ( BYTE* )( m_Password.c_str() ), ( int )m_Password.length() + 1 );
retVal->AddData( ( BYTE* )( m_SystemType.c_str() ), ( int )m_SystemType.length() + 1 );
retVal->AddData( ( BYTE* )( &m_InterfaceVersion ), sizeof( m_InterfaceVersion ) );
retVal->AddData( ( BYTE* )( &m_AddrTon ), sizeof( m_AddrTon ) );
retVal->AddData( ( BYTE* )( &m_AddrNpi ), sizeof( m_AddrNpi ) );
retVal->AddData( ( BYTE* )( m_AddressRange.c_str() ), ( int )m_AddressRange.length() + 1 );

m_Header.NTOH();

//-47
retVal->AddData( ( BYTE* ) m_OptionalParams->GetRawData()->PeekData(), m_OptionalParams->GetRawLength());
return retVal;
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetSystemId( const char* system_id ){
m_SystemId = SAFESTR( system_id );
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetPassword( const char* password ){
m_Password = SAFESTR( password );
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetSystemType( const char* system_type ){
m_SystemType = SAFESTR( system_type );
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetInterfaceVersion( BYTE interface_version ){
m_InterfaceVersion = interface_version;
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetAddrTon( BYTE addr_ton ){
m_AddrTon = addr_ton;
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetAddrNpi( BYTE addr_npi ){
m_AddrNpi = addr_npi;
}

////////////////////////////////////////////////////////
void 
CPDUBindTransceiverImpl::SetAddressRange( const char* address_range ){
m_AddressRange = SAFESTR( address_range );
}

////////////////////////////////////////////////////////
const std::string& 
CPDUBindTransceiverImpl::GetSystemId(){
return m_SystemId;
}

////////////////////////////////////////////////////////
const std::string& 
CPDUBindTransceiverImpl::GetPassword(){
return m_Password;
}

////////////////////////////////////////////////////////
const std::string&
CPDUBindTransceiverImpl::GetSystemType(){
return m_SystemType;
}

////////////////////////////////////////////////////////
BYTE 
CPDUBindTransceiverImpl::GetInterfaceVersion(){
return m_InterfaceVersion;
}

////////////////////////////////////////////////////////
BYTE 
CPDUBindTransceiverImpl::GetAddrTon(){
return m_AddrTon;
}

////////////////////////////////////////////////////////
BYTE 
CPDUBindTransceiverImpl::GetAddrNpi(){
return m_AddrNpi;
}

////////////////////////////////////////////////////////
const std::string&
CPDUBindTransceiverImpl::GetAddressRange(){
return m_AddressRange;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////