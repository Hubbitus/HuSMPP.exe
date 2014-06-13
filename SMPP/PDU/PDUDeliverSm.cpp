////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSm.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDeliverSm.h"
#include "../SMPPSessionState.h"
#include "../../Common/ubstr.h"

////////////////////////////////////////////////////////

class CPDUDeliverSmImpl : public IPDUDeliverSm{
public:
	CPDUDeliverSmImpl();
	virtual ~CPDUDeliverSmImpl();

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

	virtual const string& GetServiceType();

	virtual BYTE GetSourceAddrTon();
	virtual BYTE GetSourceAddrNpi();
	virtual const string& GetSourceAddr();

	virtual BYTE GetDestAddrTon();
	virtual BYTE GetDestAddrNpi();
	virtual const string& GetDestinationAddr();

	virtual BYTE GetEsmClass();
	virtual BYTE GetProtocolId();
	virtual BYTE GetPriorityFlag();
	virtual const string& GetScheduleDeliveryTime();
	virtual const string& GetValidityPeriod();
	virtual BYTE GetRegisteredDelivery();

	virtual BYTE GetReplaceIfPresentFlag();
	virtual BYTE GetDataCoding();
	virtual BYTE GetSmDefaultMsgId();

	virtual string GetShortMessage();

private:
	string m_ServiceType;

	BYTE m_SourceAddrTon;
	BYTE m_SourceAddrNpi;
	string m_SourceAddr;

	BYTE m_DestAddrTon;
	BYTE m_DestAddrNpi;
	string m_DestinationAddr;

	BYTE m_EsmClass;
	BYTE m_ProtocolId;
	BYTE m_PriorityFlag;
	string m_ScheduleDeliveryTime;
	string m_ValidityPeriod;
	BYTE m_RegisteredDelivery;

	BYTE m_ReplaceIfPresentFlag;
	BYTE m_DataCoding;
	BYTE m_SmDefaultMsgId;

	CH<IOctString> m_Sm;

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDeliverSm, CPDUDeliverSmImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUDeliverSmImpl )

////////////////////////////////////////////////////////
CPDUDeliverSmImpl::CPDUDeliverSmImpl(){
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
m_Header.command_id = PDU_DELIVER_SM_ID;
}

////////////////////////////////////////////////////////
CPDUDeliverSmImpl::~CPDUDeliverSmImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUDeliverSmImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
unsigned int offset = 0;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();
offset += sizeof( m_Header );
chASSERT( offset <= m_Header.command_length );
rawBuffer->Skip( sizeof( m_Header ) );

if ( IsOnlyHeader() )
return;

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
CPDUDeliverSmImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUDeliverSmImpl::GetRawData(){
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

BYTE smLength = ( BYTE ) m_Sm->GetLength();
m_Header.command_length += 1; // sm_length
m_Header.command_length += smLength; // short_message

//-47
m_Header.command_length += m_OptionalParams->GetRawLength(); // OptionalParameters

m_Header.command_id = PDU_DELIVER_SM_ID;
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
retVal->AddData( ( BYTE* ) m_OptionalParams->GetRawData()->PeekData(), m_OptionalParams->GetRawLength());
return retVal;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetServiceType( const char* service_type ){
m_ServiceType = SAFESTR( service_type );
}
  
////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetSourceAddrTon( BYTE source_addr_ton ){
m_SourceAddrTon = source_addr_ton;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetSourceAddrNpi( BYTE source_addr_npi ){
m_SourceAddrNpi = source_addr_npi;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetSourceAddr( const char* source_addr ){
m_SourceAddr = SAFESTR( source_addr );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetDestAddrTon( BYTE dest_addr_ton ){
m_DestAddrTon = dest_addr_ton;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetDestAddrNpi( BYTE dest_addr_npi ){
m_DestAddrNpi = dest_addr_npi;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetDestinationAddr( const char* destination_addr ){
m_DestinationAddr = SAFESTR( destination_addr );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetEsmClass( BYTE esm_class ){
m_EsmClass = esm_class;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetProtocolId( BYTE protocol_id ){
m_ProtocolId = protocol_id;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetPriorityFlag( BYTE priority_flag ){
m_PriorityFlag = priority_flag;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetScheduleDeliveryTime( const char* schedule_delivery_time ){
m_ScheduleDeliveryTime = SAFESTR( schedule_delivery_time );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetValidityPeriod( const char* validity_period ){
m_ValidityPeriod = SAFESTR( validity_period );
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetRegisteredDelivery( BYTE registered_delivery ){
m_RegisteredDelivery = registered_delivery;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetReplaceIfPresentFlag( BYTE replace_if_present_flag ){
m_ReplaceIfPresentFlag = replace_if_present_flag;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetDataCoding( BYTE data_coding ){
m_DataCoding = data_coding;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetSmDefaultMsgId( BYTE sm_default_msg_id ){
m_SmDefaultMsgId = sm_default_msg_id;
}

////////////////////////////////////////////////////////
void
CPDUDeliverSmImpl::SetShortMessage( const char* short_message ){
std::string sm = SAFESTR( short_message );
m_Sm->Initialize( ( const BYTE* ) sm.c_str(), ( unsigned int ) sm.length() );
}

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
const std::string&
CPDUDeliverSmImpl::GetServiceType(){
return m_ServiceType;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetSourceAddrTon(){
return m_SourceAddrTon;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetSourceAddrNpi(){
  return m_SourceAddrNpi;
}

////////////////////////////////////////////////////////
const std::string&
CPDUDeliverSmImpl::GetSourceAddr(){
return m_SourceAddr;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetDestAddrTon(){
return m_DestAddrTon;
}

////////////////////////////////////////////////////////
BYTE 
CPDUDeliverSmImpl::GetDestAddrNpi(){
return m_DestAddrNpi;
}

////////////////////////////////////////////////////////
const std::string&
CPDUDeliverSmImpl::GetDestinationAddr(){
return m_DestinationAddr;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetEsmClass(){
return m_EsmClass;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetProtocolId(){
return m_ProtocolId;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetPriorityFlag(){
return m_PriorityFlag;
}

////////////////////////////////////////////////////////
const std::string&
CPDUDeliverSmImpl::GetScheduleDeliveryTime(){
return m_ScheduleDeliveryTime;
}

////////////////////////////////////////////////////////
const std::string&
CPDUDeliverSmImpl::GetValidityPeriod(){
return m_ValidityPeriod;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetRegisteredDelivery(){
return m_RegisteredDelivery;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetReplaceIfPresentFlag(){
return m_ReplaceIfPresentFlag;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetDataCoding(){
return m_DataCoding;
}

////////////////////////////////////////////////////////
BYTE
CPDUDeliverSmImpl::GetSmDefaultMsgId(){
return m_SmDefaultMsgId;
}

////////////////////////////////////////////////////////
std::string
CPDUDeliverSmImpl::GetShortMessage(){
//+68 ВОТ ОНА КОСТЬ В ГОРЛЕ!!!!!^ Null-terminated строка для инициализации string берется.
//Если юникод, то вполне могут быть нулевые символы в последовательности, нужно указывать длину явно!
return std::string ( ( char* )m_Sm->GetData(), (( char* )m_Sm->GetData()) + m_Sm->GetLength() );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////