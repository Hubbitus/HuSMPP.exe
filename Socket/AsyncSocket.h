////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: AsyncSocket.h
// Author	: Pavel Alexeev (aka Pahan-Hubbitus)
// Created 2008-07-21
//
//	2008-09-14
//	- Delete (Comment out) using boost::asio::ip::tcp;
//	- Inherit AsyncSocket from boost::enable_shared_from_this.hpp<AsyncSocket>
//	- Add inheritance private boost::noncopyable
//	- Add define type:
//		typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
//	- Accordingly change using in ctor:
//		boost::asio::io_service& io_service
//		to
//		io_service_ptr io_service
//
//	2008-10-03
//	- Add
//		#ifdef DEBUG
//		std::string lastCalledMethod;
//		#endif
//
//	2008-10-06
//	- Add helper method void post_error(std::string errorMessage, bool doclose = true);
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////

#include "SocketEventHandler.h"
#include "PDU_message.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

////////////////////////////////////////////////////////////

//using boost::asio::ip::tcp;

////////////////////////////////////////////////////////////

typedef std::deque<PDU_message> PDU_message_queue;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;

////////////////////////////////////////////////////////////

class AsyncSocket
//?	: public boost::enable_shared_from_this<AsyncSocket>
//?	,
	: private boost::noncopyable
	{
public:
	AsyncSocket(
		int ID,
		io_service_ptr io_service,
		boost::shared_ptr<SocketEventHandler> eventHandler,
		const std::string& sAddr,
		const std::string& sPort
		);
	~AsyncSocket();

	bool isOpen(){ return socket_.is_open(); }

	boost::asio::ip::tcp::socket::endpoint_type remoteEndpoint(){ return socket_.remote_endpoint(); }
	boost::asio::ip::tcp::socket::endpoint_type localEndpoint(){ return socket_.local_endpoint(); }
	void Connect();
	void Close();
	void Write( const PDU_message& msg );
	void Write( CH<IRawBuffer> data );
	void Write( const BYTE * buf, PDU_message::LenType bufLen = 0 /*Default 0 mean get strlen(buf) */);

	CH<ISMPPSessionState> getSessionState () { return m_SessionState; };
	void setSessionState ( CH<ISMPPSessionState> state ) { if (m_SessionState) m_SessionState = state; };

	void setBinded ( bool isB = true ) { isBinded_ = isB; };
	bool isBinded () { return isBinded_; };

	int getID() { return m_nID; };

//For debug purpose. In multithreaded aplication, to see, from wht method come message (error in main)
#ifdef DEBUG
	std::string lastCalledMethod;
#endif

private:
	void do_write( PDU_message msg );
	void do_close();
	void do_connect();
	void handle_connect( const boost::system::error_code& error );
	void handle_read_header( const boost::system::error_code& error );
	void handle_read_body( const boost::system::error_code& error );
	void handle_write( const boost::system::error_code& error );

	//Helper functions
	void post_error(std::string errorMessage, bool doclose = true); //Post error to SocketEventHandler::OnError
private:
	/// Strand to ensure the connection's handlers are not called concurrently.
	boost::asio::io_service::strand strand_;
	boost::asio::ip::tcp::socket socket_;
	PDU_message read_msg_;
	PDU_message_queue write_msgs_;

	int m_nID;

	boost::asio::ip::tcp::resolver::iterator endpoint_iterator_;
	boost::shared_ptr<SocketEventHandler> m_EventHandler;

	CH<ISMPPSessionState> m_SessionState;
	bool isBinded_;

	bool disconnectInProgress_;
};//c AsyncSocket