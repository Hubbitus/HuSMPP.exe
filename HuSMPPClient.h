////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : HuSMPPClient.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-19
// 	2008-05-20 renamed to HuSMPPClient from HuSMPP
//
//	2008-09-16
//	- Add defines types:
//		typedef boost::shared_ptr<boost::thread> thread_ptr;
//		typedef boost::shared_ptr<AsyncSocket> socket_ptr;
//		And all declarations/implementations accordingly changed to thos types.
//	- Implementation enywhre changed to not copy pointer from read socket to write, and chek it instead.
//
//	2008-10-02
//	- Replace CLock m_Lock; by boost::recursive_mutex;
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "HuSMPPshared.h"
#include "HuSMSCConfig.h"

#include "SMPP/PDUEventHandler.h"
#include "Utils/Timer/CTimer.h"

#include "SMS/OutSMS.h"

#include "Socket/AsyncSocket.h"

#include "Utils/sequencer.h"

#include "SMPP/PDU/PDUUnknown.h"
#include "SMPP/PDU/PDUBindTransceiver.h"
#include "SMPP/PDU/PDUBindTransceiverResp.h"
//+90+4
#include "SMPP/PDU/PDUBindReceiver.h"
#include "SMPP/PDU/PDUBindReceiverResp.h"
#include "SMPP/PDU/PDUBindTransmitter.h"
#include "SMPP/PDU/PDUBindTransmitterResp.h"
#include "SMPP/PDU/PDUEnquireLink.h"
#include "SMPP/PDU/PDUEnquireLinkResp.h"
#include "SMPP/PDU/PDUGenericNack.h"
#include "SMPP/PDU/PDUOutbind.h"

#include "SMPP/PDU/PDUUnbind.h"
#include "SMPP/PDU/PDUUnbindResp.h"
#include "SMPP/PDU/PDUSubmitSm.h"
#include "SMPP/PDU/PDUSubmitSmResp.h"
#include "SMPP/PDU/PDUDeliverSm.h"
#include "SMPP/PDU/PDUDeliverSmResp.h"
#include "SMPP/PDU/PDUDataSm.h"
#include "SMPP/PDU/PDUDataSmResp.h"

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>

////////////////////////////////////////////////////////

typedef boost::shared_ptr<boost::thread> thread_ptr;
typedef boost::shared_ptr<AsyncSocket> socket_ptr;

////////////////////////////////////////////////////////

//For backward capability of existing code only
class ISMPPClient{};

////////////////////////////////////////////////////////
class HuSMPPClient :
				 public boost::enable_shared_from_this<HuSMPPClient>
				,public SocketEventHandler
				,public PDUEventHandler //Чтобы себя назначить обработчиком событи сокета
				,public CTimer
				,public ISMPPClient
				,public boost::noncopyable
				{
public:
	using CTimer::KillTimer;//Переопределение KillTimer из CDialog своим из CTimer

	HuSMPPClient( boost::shared_ptr<SMSCConfig> conf, long KAInterval = 15000 );
	~HuSMPPClient(void);

	virtual bool isConnected() {
/*	return (
		getReadSocket() && getReadSocket()->isOpen()
		&&
			(
			(getWriteSocket() && getWriteSocket()->isOpen()) || true
			)
	);
*/
	return ( (getReadSocket() && getReadSocket()->isOpen()) && (GetConfig()->hasTransmitter() ? getWriteSocket()->isOpen() : true) );
	};
	virtual void Connect();
	virtual void Disconnect();

	virtual void SMSCUnBind( bool closeConnectAfterUnbind = true );
	virtual bool isBinded() {
	//return getReadSocket() && getReadSocket()->isBinded() && getWriteSocket() && getWriteSocket()->isBinded();
	return ( (getReadSocket() && getReadSocket()->isBinded()) && (GetConfig()->hasTransmitter() ? getWriteSocket()->isBinded() : true) );
	};

	virtual void SubmitMessage (CH<IOutSMS> SMS);

	void SetConfig (boost::shared_ptr<SMSCConfig> sessionConfig);//A la initialize
	void SetConfig (const bool bTransceiver, const std::string sAddress, const std::string& sPort, std::string sLogin, const std::string sPass, const std::string sType,
		const std::string strDeliveryFormat,
		const BYTE nSrcTON = 1, const BYTE nSrcNPI = 1, const BYTE nDestTON = 1, const BYTE nDestNPI = 0);
	boost::shared_ptr<SMSCConfig> GetConfig();

	virtual long GetKeepAliveInterval() { return KeepAliveInterval; };//???
	virtual void SetKeepAliveInterval (long nKAI);//Seconds

	virtual void Request( CH<IPDU> request, int SocketID = Transceiver );
	virtual void RequestResp( CH<IPDU> request, DWORD sequenceNumb = 0, int SocketID = Transceiver );

	// ISocketEventHandler methods
	virtual void OnRead( const CH<IRawBuffer> data, const int SocketID );
	virtual void OnWrite( const CH<IRawBuffer> data, const int SocketID );
	virtual void OnConnect( const int SocketID );
	virtual void OnClose( const int SocketID );
	virtual void OnError( const std::string& description, const int SocketID );

	//CTimer methods
	virtual void OnTimer ( UINT nIDEvent );

	//PDUEventHandlers methods
	virtual void defaultPDUEventHandlerIn (SP<IPDU> pdu);
	virtual void defaultPDUEventHandlerOut(SP<IPDU> pdu);

	virtual void OnPDUEventHandlerIn	(SP<IPDUBindTransceiverResp> pdu);
	//+91+2
	virtual void OnPDUEventHandlerIn	(SP<IPDUBindReceiverResp> pdu);
	virtual void OnPDUEventHandlerIn	(SP<IPDUBindTransmitterResp>);
	virtual void OnPDUEventHandlerIn	(SP<IPDUSubmitSmResp> pdu);
	virtual void OnPDUEventHandlerOut	(SP<IPDUSubmitSm> pdu);
	virtual void OnPDUEventHandlerIn	(SP<IPDUUnbindResp> pdu);
	virtual void OnPDUEventHandlerIn	(SP<IPDUDeliverSm> pdu);
	virtual void OnPDUEventHandlerIn	(SP<IPDUGenericNack> pdu);
	virtual void OnPDUEventHandlerOut	(SP<IPDUGenericNack> pdu);
	virtual void OnPDUEventHandlerIn	(SP<IPDUEnquireLink> pdu);

	virtual void EnquireLink();	

//?? protected:
/*-91
	AsyncSocket& getSocket(){ return m_Socket; }

	В раздельном же режиме, getReadSocket() возвращает ссылку на сокет, обслуживающий Receiver,
	а getWriteSocket() Екфтыьшееук соответственно.
*/
	socket_ptr getReadSocket(){ return m_readSocket; }
	socket_ptr getWriteSocket(){ return m_writeSocket; }
	socket_ptr getSocketByID(int SocketID);

private:
	//-72 InOut 0 - In, 1 - Out
	void ProcessPDU( CH<IPDU> pdu, bool InOut );

	long KeepAliveInterval; //ms

	CSequencer m_Sequencer;
	boost::shared_ptr<SMSCConfig> m_SessionConfig;

	io_service_ptr io_service_;
	socket_ptr m_readSocket;
	socket_ptr m_writeSocket;
	thread_ptr pNetThread_;
	boost::shared_ptr<boost::asio::io_service::work> io_socket_work_;

	boost::recursive_mutex mutex_;

	CH<IRawBuffer> m_DataReceived;

	CH<IPDUParser> m_PDUParser;

private:
	HWND WM_messageRecipient;
	CWnd * WM_messageRecipientCWND;
public:
	void SetMessageHandler(CWnd * w){
	WM_messageRecipientCWND = w;
	};
};//class HuSMPPClient

////////////////////////////////////////////////////////

#define HuSMPPClient_CHANGE_STATE(_NewState) \
	CH<_NewState> curState; \
	curState->Initialize( static_cast<ISMPPClient*>(this) ); \
		if (getWriteSocket()) getWriteSocket()->setSessionState ( SafeCastCH<ISMPPSessionState, _NewState>( curState ) ); \
		if (getReadSocket()) getReadSocket()->setSessionState ( SafeCastCH<ISMPPSessionState, _NewState>( curState ) );