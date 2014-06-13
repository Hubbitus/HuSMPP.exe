////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : HuSMPPClient.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-19
// 	2008-05-20 renamed to HuSMPPClient from HuSMPP
//
//	2008-09-19
//	- Add sending message WM_SMPP_SOCKET_CLOSED on SocketDisconnect
//
//	2008-10-02
//	- Replace CLocalLock lock( m_Lock ); to boost::recursive_mutex::scoped_lock boost_lock(mutex_);
//
//	2008-10-06
//	- In methods Request() and RequestResp() add check if (!request->GetInSocket()->isBinded()) before write to it!
//	- Remove from OnError() method ::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_SOCKET_CLOSED, 0);
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HuSMPPClient.h"

#include "Common/Singles/singleton.h"

#include "SMPP/States/SMPPSessionClosedState.h"
#include "SMPP/States/SMPPSessionOpenState.h"
#include "SMPP/States/SMPPSessionBoundTrxState.h"
#include "SMPP/States/SMPPSessionBoundTxState.h"
#include "SMPP/States/SMPPSessionBoundRxState.h"

#include "SMPP/PDU.h"
#include "SMPP/PDUParser.h"
#include "SMPP/PDUIterator.h"

#ifdef LOG_PDU_EVENTS
#include "SMPP/PDUConstsPDUNames.h"	//Для логов
#include <iomanip>					//Для формирования строки логов
#endif

#include <boost/lexical_cast.hpp>

//////////////////////////////////////////////////////////////////
HuSMPPClient::HuSMPPClient( boost::shared_ptr<SMSCConfig> conf, long KAInterval /* = 15000 */ )
	: KeepAliveInterval (KAInterval){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

SetConfig(conf);

#ifdef LOG_PDU_EVENTS
init_PDU_DEF_NAMES();
#endif
}

//////////////////////////////////////////////////////////////////
HuSMPPClient::~HuSMPPClient(void){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
		if ( isBinded() ) SMSCUnBind();

Disconnect();
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::SetKeepAliveInterval(long nKAI){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

KeepAliveInterval = nKAI * 1000;

RestartTimer(Receiver);
RestartTimer(Transmitter);
RestartTimer(Transceiver);
}

//////////////////////////////////////////////////////////////////
//Конфигурация. Должен быть вызван ДО коннекта, иначе придется реконнектиться
void
HuSMPPClient::SetConfig (boost::shared_ptr<SMSCConfig> sessionConfig){//A la initialize
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

m_SessionConfig = sessionConfig;
}

//////////////////////////////////////////////////////////////////
//Конфигурация. Должен быть вызван ДО коннекта, иначе придется реконнектиться
boost::shared_ptr<SMSCConfig>
HuSMPPClient::GetConfig (){
return m_SessionConfig;
}

//////////////////////////////////////////////////////////////////
void //A la initialize
HuSMPPClient::SetConfig (const bool bTransceiver, const std::string sAddress, const std::string& sPort, const std::string sLogin, const std::string sPass, const std::string sType,
	 	const std::string strDeliveryFormat,
		const BYTE nSrcTON/* = 1*/, const BYTE nSrcNPI/* = 1*/, const BYTE nDestTON/* = 1*/, const BYTE nDestNPI/* = 0*/){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
	
//m_SessionConfig->Initialize( "127.0.0.1", 2775, "smppclient", "pass", "SMSStudio" );
SetConfig (boost::shared_ptr<SMSCConfig>(new SMSCConfig(bTransceiver, sAddress, sPort, sLogin, sPass, sType, strDeliveryFormat, nSrcTON, nSrcNPI, nDestTON, nDestNPI)));
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::Connect(){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

	//Асинхронный коннект, остальные операции в OnConnect и OnError
	if ( getReadSocket() && getReadSocket()->isOpen()){
	GETLOG->AddToLog( "HuSMPPClient::Connect(): Read socket connected, do Disconnect first. Return." );
	return;
	}

HuSMPPClient_CHANGE_STATE(ISMPPSessionClosedState)

	if (! io_service_){
	io_service_ = io_service_ptr(new boost::asio::io_service);
	io_socket_work_ = boost::shared_ptr<boost::asio::io_service::work> (new boost::asio::io_service::work(*io_service_));
	}

	//This can't be created in constructor
	//http://www.boost.org/doc/libs/1_35_0/libs/smart_ptr/sp_techniques.html#in_constructor
	//http://www.boost.org/doc/libs/1_35_0/libs/smart_ptr/sp_techniques.html#weak_without_shared
	if (GetConfig()->isTransceiver()){
		if (!m_readSocket)
		m_readSocket = socket_ptr(new AsyncSocket(Transceiver, io_service_, shared_from_this(), GetConfig()->GetServerAddr(), GetConfig()->GetServerPort()));
	}
	else{
		if ( getWriteSocket() && getWriteSocket()->isOpen() ){
		GETLOG->AddToLog( "HuSMPPClient::Connect(): Read socket connected, do SocketDisconnect first. Return." );
		return;
		}
	
		if (!m_writeSocket)
		m_writeSocket	= socket_ptr(new AsyncSocket(Transmitter, io_service_, shared_from_this(), GetConfig()->GetServerAddr(), GetConfig()->GetServerPort()));
		if (!m_readSocket)
		m_readSocket	= socket_ptr(new AsyncSocket(Receiver, io_service_, shared_from_this(), GetConfig()->GetServerAddr(), GetConfig()->GetServerPort()));

	getWriteSocket()->Connect();

	//After start of jobs, start new thread for it io_service
	//? Не уверен что требуется еще один тред...
	//? boost::thread writeThread(boost::bind(&boost::asio::io_service::run, &io_service_));
	}
//ReadSocket present always
getReadSocket()->Connect();

//After start of jobs, start new thread for it io_service. Or replace if was.
pNetThread_ = thread_ptr( new boost::thread (boost::bind(&boost::asio::io_service::run, io_service_)) );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::Disconnect(){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

HuSMPPClient_CHANGE_STATE(ISMPPSessionClosedState)

	if (isBinded())
	GETLOG->AddToLog ( "HuSMPPClient::SocketDisconnect() without UnBind!" );

	//It may be invoked fore insurance before socket creation
	if (getReadSocket() && getReadSocket()->isOpen()) getReadSocket()->Close();
	if (getWriteSocket() && getWriteSocket()->isOpen()) getWriteSocket()->Close();

	if (pNetThread_){
	//Do NOT join to not switch to other thread an mix it!
//	pNetThread_->join(); //Wait for finish ??? Why it is not returned???
	bool joinRes = pNetThread_->timed_join( boost::posix_time::seconds(2) ); //Wait for finish 2 seconds

	//Then terminate
	// detach() called from destructor, which will be invoked from shared_ptr after next release pointer
	pNetThread_.reset();
	}

	if (io_service_){
	io_service_->stop();
	io_service_->reset();
//?	io_service_.reset();

	Sleep(1500); //1 second at least. This is mandatory!
	//Poll rest
	boost::system::error_code err;
	size_t pol_res = io_service_->poll(err);
	Sleep(0); //For breakpoint
	}
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::Request( CH<IPDU> request, int SocketID /* = Transceiver */ ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

DWORD seqNumber = m_Sequencer;
request->SetSequenceNumber( seqNumber );

	if ( !request->GetInSocket() ) request->SetInSocket( getSocketByID( SocketID ) );

	// @todo - add throwing exception and handle it!
	if (!request->GetInSocket()->isOpen()){
	#ifdef DEBUG_SOCKET
	GETLOG->AddToLog( ("Attempt Request to NOT opened socket (" + boost::lexical_cast<std::string>(SocketID) + ")").c_str() );
	#endif
	return;
	}
request->GetInSocket()->Write( request->GetRawData() );

//-49
//-72
ProcessPDU( request, 1 );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::RequestResp( CH<IPDU> request, DWORD sequenceNumb, int SocketID /* = Transceiver */ ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

	if (sequenceNumb > 0)//Если передан отдельно. В обратном случае считаем что уже установлен.
	request->SetSequenceNumber( sequenceNumb );

	if ( !request->GetInSocket() ) request->SetInSocket( getSocketByID( SocketID ) );

	// @todo - add throwing exception and handle it!
	if (!request->GetInSocket()->isOpen()){
	#ifdef DEBUG_SOCKET
	GETLOG->AddToLog( ("Attempt RequestResp to NOT opened socket (" + boost::lexical_cast<std::string>(SocketID) + ")").c_str() );
	#endif
	return;
	}
request->GetInSocket()->Write( request->GetRawData() );

//-49
//-72
ProcessPDU( request, 1 );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::SMSCUnBind(bool closeConnectAfterUnbind /* = true */ ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

GetConfig()->setCloseConnectAfterUnbind(closeConnectAfterUnbind);

	if ( getReadSocket()->isBinded() ){
	CH<IPDUUnbind> unbindPDU;
	Request( SafeCastCH<IPDU, IPDUUnbind>( unbindPDU ), getReadSocket()->getID() );
	getReadSocket()->setBinded( false );
	}

	if ( getWriteSocket() && getWriteSocket()->isBinded() ){
	CH<IPDUUnbind> unbindPDU;
	Request( SafeCastCH<IPDU, IPDUUnbind>( unbindPDU ), getWriteSocket()->getID() );
	getWriteSocket()->setBinded( false );
	}

HuSMPPClient_CHANGE_STATE(ISMPPSessionOpenState)
}

//////////////////////////////////////////////////////////////////
//-72 InOut 0 - In, 1 - Out
void
HuSMPPClient::ProcessPDU( CH<IPDU> pdu, bool InOut ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

/*91
CH<IAction> action = pdu->ProcessState( ( ( ISMPPSessionState* ) m_SessionState ) );
m_SessionState = action->Perform( pdu, m_SessionState );
*/

pdu->GetInSocket()->setSessionState(
	pdu->ProcessState()->Perform( pdu )
);

#ifdef DEBUG_SOCKET
GETLOG->AddToLog( ("HuSMPPClient - new state " + std::string(pdu->GetInSocket()->getSessionState()->GetClassName())).c_str() , true );
#endif

	if (InOut) pdu->ProcessPDUEventOut (this);
	else pdu->ProcessPDUEventIn (this);

//Таймер должен быть сброшен, чтобы не слать зря EnquireLink
//ResetTimer(const_cast<STimer &>(STimerByIDEvent(m_EnqLinkTimer_nIDEvent)));
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::SubmitMessage (CH<IOutSMS> SMS){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

IOutSMS::SMSPairVector::const_iterator sms = SMS->GetPDUs().begin();

	//Каждая СМС может быть разрезана на несколько частей, но как минимум 1 будет полюбому
	while (sms != SMS->GetPDUs().end()){
	Request( SafeCastCH<IPDU, IPDUSubmitSm>( sms->first ), getWriteSocket() ? getWriteSocket()->getID() : getReadSocket()->getID());
	++sms;
	}

//Ну и в КЕШ это, ждать RESP
//-87 
GETRESPCACHE->AddSMS(SMS);
}

////////////////////////////////////////////////////////
// ISocketEventHandler methods
////////////////////////////////////////////////////////
void
HuSMPPClient::OnRead( const CH<IRawBuffer> data, const int SocketID ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
#ifdef DEBUG_SOCKET
GETLOG->AddToLog( ("HuSMPPClient::OnRead(" + boost::lexical_cast<std::string>(SocketID) + ")").c_str(), true );
#endif

m_DataReceived->AddData( data->PeekData(), data->GetAvailableDataSize() );
CH<IPDUIterator> iter = m_PDUParser->ParsePDU( m_DataReceived, getSocketByID( SocketID ) );

//-72
	while ( iter->More() ) ProcessPDU( iter->Next(), 0 );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnWrite( const CH<IRawBuffer> data, const int SocketID ){
#ifdef DEBUG_SOCKET
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
GETLOG->AddToLog( ("HuSMPPClient::OnWrite(" + boost::lexical_cast<std::string>(SocketID) + ")").c_str(), true );
#endif
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnConnect( const int SocketID ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

HuSMPPClient_CHANGE_STATE(ISMPPSessionOpenState)

#ifdef DEBUG_SOCKET
std::ostringstream tBuf;

tBuf << "HuSMPPClient::OnConnect(" << SocketID << ") - " << getSocketByID(SocketID)->remoteEndpoint().address().to_string() << ":" << getSocketByID(SocketID)->remoteEndpoint().port();
GETLOG->AddToLog( tBuf.str().c_str() );
#endif

GETLOG->AddToLog(("Connection " + boost::lexical_cast<std::string>(SocketID) + " to SMSC sucseeded").c_str());

	switch (SocketID){
	case Transceiver: {
	CH<IPDUBindTransceiver> bindPDU;
	bindPDU->SetSystemId( GetConfig()->GetSystemId().c_str() );
	bindPDU->SetPassword( GetConfig()->GetPassword().c_str() );
	bindPDU->SetSystemType( GetConfig()->GetSystemType().c_str() );
	Request( SafeCastCH<IPDU, IPDUBindTransceiver>( bindPDU ), SocketID );
	break;
	}

	case Receiver: {
	CH<IPDUBindReceiver> bindPDU;
	bindPDU->SetSystemId( GetConfig()->GetSystemId().c_str() );
	bindPDU->SetPassword( GetConfig()->GetPassword().c_str() );
	bindPDU->SetSystemType( GetConfig()->GetSystemType().c_str() );
	Request( SafeCastCH<IPDU, IPDUBindReceiver>( bindPDU ), SocketID );
	break;
	}

	case Transmitter: {
	CH<IPDUBindTransmitter> bindPDU;
	bindPDU->SetSystemId( GetConfig()->GetSystemId().c_str() );
	bindPDU->SetPassword( GetConfig()->GetPassword().c_str() );
	bindPDU->SetSystemType( GetConfig()->GetSystemType().c_str() );
	Request( SafeCastCH<IPDU, IPDUBindTransmitter>( bindPDU ), SocketID );
	break;
	}

	default:
	throw new std::exception("SocketID not found in HuSMPPClient::OnConnect!");
	}

::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_SOCKET_CONNECTED, 0);
GETLOG->AddToLog( "Trying binding to SMSC..." );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnClose( const int SocketID ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

std::ostringstream tBuf;
tBuf << "HuSMPPClient::OnClose(" << SocketID << ") - " << GetConfig()->GetServerAddr() << ":" << GetConfig()->GetServerPort();
GETLOG->AddToLog( tBuf.str().c_str() );

HuSMPPClient_CHANGE_STATE(ISMPPSessionClosedState)

//If resp hasn't been got clear waiting cache.
GETRESPCACHE->FlushAllCacheToFailed();

::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_SOCKET_CLOSED, 0);
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnError( const std::string& description, const int SocketID ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

GETLOG->AddToLog( ("HuSMPPClient::OnError(" + boost::lexical_cast<std::string>(SocketID) + ") - " + description).c_str() );
}

///////////////////////////////////////
///////CTimer
///////////////////////////////////////
void
HuSMPPClient::OnTimer( UINT nIDEvent ){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
//MessageBeep(0xFFFFFFFF);   // Beep
//GETLOG->AddToLog( ("HuSMPPClient::OnTimer(" + uint2str(nIDEvent) + ")").c_str() );

//Пока таймер только для EnquireLink используем
//Позже реализовать еще таймауты ожидания ответов
EnquireLink();
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::EnquireLink(){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
//Ответ посылается в CEnquireLinkActionImpl::Perform, самому не надо!!
	//Timer may fire when socket disconnected and destroyed!
	if (getReadSocket() && getReadSocket()->isBinded()){
	CH<IPDUEnquireLink> enqLink;
	Request( SafeCastCH<IPDU, IPDUEnquireLink>( enqLink ), getReadSocket()->getID() );
	}

	if ( getWriteSocket() && getWriteSocket()->isBinded()){
	CH<IPDUEnquireLink> enqLink;
	Request( SafeCastCH<IPDU, IPDUEnquireLink>( enqLink ), getWriteSocket() ? getWriteSocket()->getID() : getReadSocket()->getID() );
	}
}

//////////////////////////////////////////////////////////////////
boost::shared_ptr<AsyncSocket>
HuSMPPClient::getSocketByID(int SocketID){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
	switch (SocketID){
	case Transceiver:
	case Receiver:
	return getReadSocket();
	break;

	case Transmitter:
	return getWriteSocket();
	break;

	default:
	throw new std::exception("Socket ID not found!");
	}
}

////////////////////////////////////////////////////////
// PDUEventHandler methods
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void
HuSMPPClient::defaultPDUEventHandlerIn(SP<IPDU> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

#ifdef LOG_PDU_EVENTS
std::ostringstream strBuffer;
//strBuffer.fill('#');
strBuffer.setf(std::ostringstream::right, std::ostringstream::adjustfield);
strBuffer.setf(std::ostringstream::hex, std::ostringstream::basefield);
strBuffer.setf(std::ostringstream::showbase);

strBuffer
	<< "HuSMPPClient::defaultPDU.E.H.IN. Process PDU: (" << PDU_DEF_NAMES[pdu->GetHeader().command_id] << ")" << std::endl
	<< "\t" << "command:" << std::setw(11) << "_id" << std::setw(10) << "_length" << std::setw(10) << "_status" << "\t" << "sequence_number" << std::endl
	<< "\t" << std::setw(19) << pdu->GetHeader().command_id << std::setw(10) << pdu->GetHeader().command_length << std::setw(10) << pdu->GetHeader().command_status << "\t" << std::left << pdu->GetHeader().sequence_number << '(' << std::dec << pdu->GetHeader().sequence_number << ")";
GETLOG->AddToLog(strBuffer.str().c_str(), true);
#endif
}

////////////////////////////////////////////////////////
void
HuSMPPClient::defaultPDUEventHandlerOut(SP<IPDU> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

#ifdef LOG_PDU_EVENTS
std::ostringstream strBuffer;
//strBuffer.fill('#');
strBuffer.setf(std::ostringstream::right, std::ostringstream::adjustfield);
strBuffer.setf(std::ostringstream::hex, std::ostringstream::basefield);
strBuffer.setf(std::ostringstream::showbase);

strBuffer
	<< "HuSMPPClient::defaultPDU.E.H.Out. Process PDU: (" << PDU_DEF_NAMES[pdu->GetHeader().command_id] << ")" << std::endl
	<< "\t" << "command:" << std::setw(11) << "_id" << std::setw(10) << "_length" << std::setw(10) << "_status" << "\t" << "sequence_number" << std::endl
	<< "\t" << std::setw(19) << pdu->GetHeader().command_id << std::setw(10) << pdu->GetHeader().command_length << std::setw(10) << pdu->GetHeader().command_status << "\t" << std::left << pdu->GetHeader().sequence_number << '(' << std::dec << pdu->GetHeader().sequence_number << ")";
GETLOG->AddToLog(strBuffer.str().c_str(), true);
#endif
}

//////////////////////////////////////////////////////////////////
//Уведомление об ответе ЛОГИНА на SMSC
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUBindReceiverResp> pdu) {
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUBindReceiverResp*)pdu);

	if (pdu->GetHeader().command_status != 0){//Bind failed
	GETLOG->AddToLog( ("HuSMPPClient::OnPDUE.H.In - Bind Receiver Failed :( (" + ESMEdescription(pdu->GetHeader().command_status) + ")").c_str() );
	}
	else{
	GETLOG->AddToLog( "HuSMPPClient::OnPDUE.H.In - Bind Receiver Sucsesfull :);)" );
	StartTimer (Receiver, GetKeepAliveInterval(), "EnquireLink_receiver");
	pdu->GetInSocket()->setBinded();
		if ( isBinded() ){
		::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_BINDED, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////
//Уведомление об ответе ЛОГИНА на SMSC
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUBindTransmitterResp> pdu) {
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUBindTransmitterResp*)pdu);

	if (pdu->GetHeader().command_status != 0){//Bind failed
	GETLOG->AddToLog( ("HuSMPPClient::OnPDUE.H.In - Bind Transmitter Failed :( (" + ESMEdescription(pdu->GetHeader().command_status) + ")").c_str() );
	}
	else{
	GETLOG->AddToLog( "HuSMPPClient::OnPDUE.H.In - Bind Transmitter Sucsesfull :);)" );
	StartTimer (Transmitter, GetKeepAliveInterval(), "EnquireLink_transmitter");
	pdu->GetInSocket()->setBinded();
		if ( isBinded() ){
		::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_BINDED, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////
//Уведомление об ответе ЛОГИНА на SMSC
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUBindTransceiverResp> pdu) {
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUBindTransceiverResp*)pdu);

	if (pdu->GetHeader().command_status != 0){//Bind failed
	GETLOG->AddToLog( ("HuSMPPClient::OnPDUE.H.In - Bind Transceiver Failed :( (" + ESMEdescription(pdu->GetHeader().command_status) + ")").c_str() );
	}
	else{
	GETLOG->AddToLog( "HuSMPPClient::OnPDUE.H.In - Bind Tranceiver Sucsesfull :);)" );
	StartTimer (Transceiver, GetKeepAliveInterval(), "EnquireLink_transceiver");
	pdu->GetInSocket()->setBinded();
	//In Transceiver we can assume what we full binded now, socket single
	::PostMessage(WM_messageRecipientCWND->GetSafeHwnd(), WM_COMMAND, WM_SMPP_BINDED, 0);
	}
}

//////////////////////////////////////////////////////////////////
//Уведомление о приеме на отправку СМСки
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUSubmitSmResp> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUSubmitSmResp*)pdu);

//-64 Добавляем в кеш и шлем сообщение главному окну об этом
GETRESPCACHE->AddRESP(pdu);
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUUnbindResp> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUUnbindResp*)pdu);
	if (pdu->GetHeader().command_status == 0){//Успешно анбинднулись
	GETLOG->AddToLog( ("HuSMPPClient::OnPDU.E.H.In - UNBind'нулись (seq=" + strUtils::uint2str(pdu->GetSequenceNumber()) + ")").c_str() );
	}
	else{
	GETLOG->AddToLog( ("HuSMPPClient::OnPDU.E.H.In - Ошибка при UnBind'е! (seq=" + strUtils::uint2str(pdu->GetSequenceNumber()) + ")").c_str() );
	}

	if (GetConfig()->getCloseConnectAfterUnbind()){
	Disconnect();
	}
}

//////////////////////////////////////////////////////////////////
//отправка СМСки
void
HuSMPPClient::OnPDUEventHandlerOut (SP<IPDUSubmitSm> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
GETLOG->AddToLog( ("HuSMPPClient::OnPDU.E.H.Out - Отправляется SMS для " + pdu->GetDestinationAddr()).c_str());
}

//////////////////////////////////////////////////////////////////
//Получение СМСки, надо ответить resp
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUDeliverSm> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

defaultPDUEventHandlerIn ((IPDU*)(IPDUDeliverSm*)pdu);

CH<IPDUDeliverSmResp> deliverResp;
RequestResp( SafeCastCH<IPDU, IPDUDeliverSmResp>( deliverResp ), pdu->GetSequenceNumber(), pdu->GetInSocket()->getID() );

//-61 Добавляем в КЕШ и отправляем сообщение забрать
CH<IPDUDeliverSm> SMS;
SMS->Initialize (pdu->GetRawData(), pdu->GetInSocket());
GETSMSCACHE->AddPDU( SafeCastCH<IPDU, IPDUDeliverSm>(SMS) );
	if((WM_messageRecipient = WM_messageRecipientCWND->GetSafeHwnd())) ::PostMessage(WM_messageRecipient, WM_COMMAND, WM_SMPP_MESSAGE_RECIVED, 0);
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUEnquireLink> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);

//Answer to incoming EnquireLink
CH<IPDUEnquireLinkResp> enqLinkResp;
RequestResp( SafeCastCH<IPDU, IPDUEnquireLinkResp>( enqLinkResp ), pdu->GetSequenceNumber(), pdu->GetInSocket()->getID() );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnPDUEventHandlerIn (SP<IPDUGenericNack> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
std::ostringstream strBuffer;
strBuffer
	<< "HuSMPPClient::OnPDU.E.H.In PDUGenericNack ЧТО-ТО НЕ ТАК! SequensNo:" << pdu->GetSequenceNumber()
	<< ", Status:" << pdu->GetHeader().command_status;
	GETLOG->AddToLog( strBuffer.str().c_str() );
}

//////////////////////////////////////////////////////////////////
void
HuSMPPClient::OnPDUEventHandlerOut (SP<IPDUGenericNack> pdu){
boost::recursive_mutex::scoped_lock boost_lock(mutex_);
std::ostringstream strBuffer;
strBuffer
	<< "HuSMPPClient::OnPDU.E.H.Out PDUGenericNack ЧТО-ТО НЕ ТАК! SequensNo:" << pdu->GetSequenceNumber()
	<< ", Status:" << pdu->GetHeader().command_status;
	GETLOG->AddToLog( strBuffer.str().c_str() );
}
