////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSm.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUSubmitSm.h"
#include "../SMPPSessionState.h"
#include "../../Common/ubstr.h"

////////////////////////////////////////////////////////

class CPDUSubmitSmImpl : public IPDUSubmitSm{
public:
	CPDUSubmitSmImpl();
	virtual ~CPDUSubmitSmImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

	virtual void SetServiceType( const char* service_type );

	virtual void SetSourceAddrTon( BYTE source_addr_ton );
	virtual void SetSourceAddrNpi( BYTE source_addr_npi );
	virtual void SetSourceAddr( const char* source_addr );

	virtual void SetDestAddrTon( BYTE dest_addr_ton );
	virtual void SetDestAddrNpi( BYTE dest_addr_npi );
	virtual void SetDestinationAddr( const char* destination_addr );

	virtual void SetEsmClass( BYTE esm_class );
	virtual void SetProtocolId( BYTE protocol_id );
	virtual void SetPriorityFlag( BYTE priority_flag );
	virtual void SetScheduleDeliveryTime( const char* schedule_delivery_time );
	virtual void SetValidityPeriod( const char* validity_period );
	virtual void SetRegisteredDelivery( BYTE registered_delivery );

	virtual void SetReplaceIfPresentFlag( BYTE replace_if_present_flag );
	virtual void SetDataCoding( BYTE data_coding );
	virtual void SetSmDefaultMsgId( BYTE sm_default_msg_id );

	virtual void SetShortMessage( const char* short_message );
	//-71
	virtual void SetShortMessage( const std::string short_message );

	virtual const std::string& GetServiceType();

	virtual BYTE GetSourceAddrTon();
	virtual BYTE GetSourceAddrNpi();
	virtual const std::string& GetSourceAddr();

	virtual BYTE GetDestAddrTon();
	virtual BYTE GetDestAddrNpi();
	virtual const std::string& GetDestinationAddr();

	virtual BYTE GetEsmClass();
	virtual BYTE GetProtocolId();
	virtual BYTE GetPriorityFlag();
	virtual const std::string& GetScheduleDeliveryTime();
	virtual const std::string& GetValidityPeriod();
	virtual BYTE GetRegisteredDelivery();

	virtual BYTE GetReplaceIfPresentFlag();
	virtual BYTE GetDataCoding();
	virtual BYTE GetSmDefaultMsgId();

	virtual const std::string GetShortMessage();

private:
	std::string m_ServiceType;

	BYTE m_SourceAddrTon;
	BYTE m_SourceAddrNpi;
	std::string m_SourceAddr;

	BYTE m_DestAddrTon;
	BYTE m_DestAddrNpi;
	std::string m_DestinationAddr;

	BYTE m_EsmClass;
	BYTE m_ProtocolId;
	BYTE m_PriorityFlag;
	std::string m_ScheduleDeliveryTime;
	std::string m_ValidityPeriod;
	BYTE m_RegisteredDelivery;

	BYTE m_ReplaceIfPresentFlag;
	BYTE m_DataCoding;
	BYTE m_SmDefaultMsgId;

	CH<IOctString> m_Sm;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUSubmitSm, CPDUSubmitSmImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUSubmitSmImpl )

////////////////////////////////////////////////////////
CPDUSubmitSmImpl::CPDUSubmitSmImpl(){
m_ServiceType = "";
m_SourceAddrTon = 0;
m_SourceAddrNpi = 0;
m_SourceAddr = "";

m_DestAddrTon = 0;
m_DestAddrNpi = 0;
m_DestinationAddr = "";

m_EsmClass = 0;
m_ProtocolId = 0;
m_PriorityFlag = 0;

m_ScheduleDeliveryTime = "";
m_ValidityPeriod = "";
m_RegisteredDelivery = 0;

m_ReplaceIfPresentFlag = 0;
m_DataCoding = 0;
m_SmDefaultMsgId = 0;

m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_SUBMIT_SM_ID;
}

////////////////////////////////////////////////////////
CPDUSubmitSmImpl::~CPDUSubmitSmImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUSubmitSmImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
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

m_ServiceType = rawBuffer->GetCString( 6 );
offset += ( unsigned int ) m_ServiceType.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_SourceAddrTon = rawBuffer->GetBYTE();
offset += sizeof( m_SourceAddrTon );
chASSERT( offset <= m_Header.command_length );

m_SourceAddrNpi = rawBuffer->GetBYTE();
offset += sizeof( m_SourceAddrNpi );
chASSERT( offset <= m_Header.command_length );

m_SourceAddr = rawBuffer->GetCString( 21 );
offset += ( unsigned int ) m_SourceAddr.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_DestAddrTon = rawBuffer->GetBYTE();
offset += sizeof( m_DestAddrTon );
chASSERT( offset <= m_Header.command_length );

m_DestAddrNpi = rawBuffer->GetBYTE();
offset += sizeof( m_DestAddrNpi );
chASSERT( offset <= m_Header.command_length );

m_DestinationAddr = rawBuffer->GetCString( 21 );
offset += ( unsigned int ) m_DestinationAddr.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_EsmClass = rawBuffer->GetBYTE();
offset += sizeof( m_EsmClass );
chASSERT( offset <= m_Header.command_length );

m_ProtocolId = rawBuffer->GetBYTE();
offset += sizeof( m_ProtocolId );
chASSERT( offset <= m_Header.command_length );

m_PriorityFlag = rawBuffer->GetBYTE();
offset += sizeof( m_PriorityFlag );
chASSERT( offset <= m_Header.command_length );

m_ScheduleDeliveryTime = rawBuffer->GetCString( 1 );
offset += ( unsigned int ) m_ScheduleDeliveryTime.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_ValidityPeriod = rawBuffer->GetCString( 1 );
offset += ( unsigned int ) m_ValidityPeriod.length() + 1;
chASSERT( offset <= m_Header.command_length );

m_RegisteredDelivery = rawBuffer->GetBYTE();
offset += sizeof( m_RegisteredDelivery );
chASSERT( offset <= m_Header.command_length );

m_ReplaceIfPresentFlag = rawBuffer->GetBYTE();
offset += sizeof( m_ReplaceIfPresentFlag );
chASSERT( offset <= m_Header.command_length );

m_DataCoding = rawBuffer->GetBYTE();
offset += sizeof( m_DataCoding );
chASSERT( offset <= m_Header.command_length );

m_SmDefaultMsgId = rawBuffer->GetBYTE();
offset += sizeof( m_SmDefaultMsgId );
chASSERT( offset <= m_Header.command_length );

m_Sm = rawBuffer->GetOctString() ;
offset += m_Sm->GetLength() + 1;
chASSERT( offset <= m_Header.command_length );

m_OptionalParams->Initialize( rawBuffer );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUSubmitSmImpl::GetRawData(){
CH<IRawBuffer> retVal;

m_Header.command_length = sizeof( m_Header );
m_Header.command_length += ( DWORD ) m_ServiceType.length() + 1;

m_Header.command_length += 1; // source_addr_ton
m_Header.command_length += 1; // source_addr_npi
m_Header.command_length += ( DWORD ) m_SourceAddr.length() + 1;

m_Header.command_length += 1; // dest_addr_ton
m_Header.command_length += 1; // dest_addr_npi
m_Header.command_length += ( DWORD ) m_DestinationAddr.length() + 1;

m_Header.command_length += 1; // esm_class
m_Header.command_length += 1; // protocol_id
m_Header.command_length += 1; // priority_flag
m_Header.command_length += ( DWORD ) m_ScheduleDeliveryTime.length() + 1; // schedule_delivery_time
m_Header.command_length += ( DWORD ) m_ValidityPeriod.length() + 1; // validity_period
m_Header.command_length += 1; // registered_delivery
m_Header.command_length += 1; // replace_if_present_flag
m_Header.command_length += 1; // data_coding
m_Header.command_length += 1; // sm_default_msg_id

// 254 max length by SMPPv3.4
BYTE smLength = ( BYTE ) m_Sm->GetLength();
m_Header.command_length += 1; // sm_length
m_Header.command_length += smLength; // short_message

//-47
m_Header.command_length += m_OptionalParams->GetRawLength(); // OptionalParameters

m_Header.command_id = PDU_SUBMIT_SM_ID;
m_Header.command_status = ESME_ROK;

m_Header.HTON();

retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
retVal->AddData( ( BYTE* )( m_ServiceType.c_str() ), ( int )m_ServiceType.length() + 1 );
retVal->AddData( ( BYTE* )( &m_SourceAddrTon ), sizeof( m_SourceAddrTon ) );
retVal->AddData( ( BYTE* )( &m_SourceAddrNpi ), sizeof( m_SourceAddrNpi ) );
retVal->AddData( ( BYTE* )( m_SourceAddr.c_str() ), ( int )m_SourceAddr.length() + 1 );

retVal->AddData( ( BYTE* )( &m_DestAddrTon ), sizeof( m_DestAddrTon ) );
retVal->AddData( ( BYTE* )( &m_DestAddrNpi ), sizeof( m_DestAddrNpi ) );
retVal->AddData( ( BYTE* )( m_DestinationAddr.c_str() ), ( int )m_DestinationAddr.length() + 1 );

retVal->AddData( ( BYTE* )( &m_EsmClass ), sizeof( m_EsmClass ) );
retVal->AddData( ( BYTE* )( &m_ProtocolId ), sizeof( m_ProtocolId ) );
retVal->AddData( ( BYTE* )( &m_PriorityFlag ), sizeof( m_PriorityFlag ) );
retVal->AddData( ( BYTE* )( m_ScheduleDeliveryTime.c_str() ), ( int )m_ScheduleDeliveryTime.length() + 1 );
retVal->AddData( ( BYTE* )( m_ValidityPeriod.c_str() ), ( int )m_ValidityPeriod.length() + 1 );
retVal->AddData( ( BYTE* )( &m_RegisteredDelivery ), sizeof( m_RegisteredDelivery ) );

retVal->AddData( ( BYTE* )( &m_ReplaceIfPresentFlag ), sizeof( m_ReplaceIfPresentFlag ) );
retVal->AddData( ( BYTE* )( &m_DataCoding ), sizeof( m_DataCoding ) );
retVal->AddData( ( BYTE* )( &m_SmDefaultMsgId ), sizeof( m_SmDefaultMsgId ) );

retVal->AddData( ( BYTE* )( &smLength ), sizeof( smLength ) );

	if ( smLength ) retVal->AddData( m_Sm->GetData(), smLength );

m_Header.NTOH();

//-47
retVal->AddData( 
	m_OptionalParams->GetRawData()->PeekData(),
	m_OptionalParams->GetRawLength()
);

return retVal;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetServiceType( const char* service_type ){
m_ServiceType = SAFESTR( service_type );
}
  
////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetSourceAddrTon( BYTE source_addr_ton ){
m_SourceAddrTon = source_addr_ton;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetSourceAddrNpi( BYTE source_addr_npi ){
m_SourceAddrNpi = source_addr_npi;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetSourceAddr( const char* source_addr ){
m_SourceAddr = SAFESTR( source_addr );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetDestAddrTon( BYTE dest_addr_ton ){
m_DestAddrTon = dest_addr_ton;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetDestAddrNpi( BYTE dest_addr_npi ){
m_DestAddrNpi = dest_addr_npi;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetDestinationAddr( const char* destination_addr ){
m_DestinationAddr = SAFESTR( destination_addr );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetEsmClass( BYTE esm_class ){
m_EsmClass = esm_class;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetProtocolId( BYTE protocol_id ){
m_ProtocolId = protocol_id;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetPriorityFlag( BYTE priority_flag ){
m_PriorityFlag = priority_flag;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetScheduleDeliveryTime( const char* schedule_delivery_time ){
m_ScheduleDeliveryTime = SAFESTR( schedule_delivery_time );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetValidityPeriod( const char* validity_period ){
m_ValidityPeriod = SAFESTR( validity_period );
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetRegisteredDelivery( BYTE registered_delivery ){
m_RegisteredDelivery = registered_delivery;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetReplaceIfPresentFlag( BYTE replace_if_present_flag ){
m_ReplaceIfPresentFlag = replace_if_present_flag;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetDataCoding( BYTE data_coding ){
m_DataCoding = data_coding;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetSmDefaultMsgId( BYTE sm_default_msg_id ){
m_SmDefaultMsgId = sm_default_msg_id;
}

////////////////////////////////////////////////////////
void
CPDUSubmitSmImpl::SetShortMessage( const char* short_message ){
std::string sm = SAFESTR( short_message );
m_Sm->Initialize( ( const BYTE* ) sm.c_str(), ( unsigned int ) sm.length() );
}

////////////////////////////////////////////////////////
//-71 My
void
CPDUSubmitSmImpl::SetShortMessage( const std::string short_message ){
m_Sm->Initialize( ( const BYTE* ) short_message.c_str(), ( unsigned int ) short_message.length() );
}

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmImpl::GetServiceType(){
return m_ServiceType;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetSourceAddrTon(){
return m_SourceAddrTon;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetSourceAddrNpi(){
return m_SourceAddrNpi;
}

////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmImpl::GetSourceAddr(){
return m_SourceAddr;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetDestAddrTon(){
return m_DestAddrTon;
}

////////////////////////////////////////////////////////
BYTE 
CPDUSubmitSmImpl::GetDestAddrNpi(){
return m_DestAddrNpi;
}

////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmImpl::GetDestinationAddr(){
return m_DestinationAddr;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetEsmClass(){
return m_EsmClass;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetProtocolId(){
return m_ProtocolId;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetPriorityFlag(){
return m_PriorityFlag;
}

////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmImpl::GetScheduleDeliveryTime(){
return m_ScheduleDeliveryTime;
}

////////////////////////////////////////////////////////
const std::string&
CPDUSubmitSmImpl::GetValidityPeriod(){
return m_ValidityPeriod;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetRegisteredDelivery(){
return m_RegisteredDelivery;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetReplaceIfPresentFlag(){
return m_ReplaceIfPresentFlag;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetDataCoding(){
return m_DataCoding;
}

////////////////////////////////////////////////////////
BYTE
CPDUSubmitSmImpl::GetSmDefaultMsgId(){
return m_SmDefaultMsgId;
}

////////////////////////////////////////////////////////
const std::string
CPDUSubmitSmImpl::GetShortMessage(){
std::string retVal;

	if ( m_Sm->GetLength() > 0 ) retVal = ( char* ) ( m_Sm->GetData() );

return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////