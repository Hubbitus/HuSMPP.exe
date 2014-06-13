////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: AsyncSocket.cpp
// Author	: Pavel Alexeev (aka Pahan-Hubbitus)
// Created 2008-07-21
//
//	2008-09-14
//	- All "this" in *private* methods! replaced by shared_from_this().
//		So, we can't replace it in public methods - errors come! I can't understabd why :(
//
//	2008-10-04 22:31
//	- Move all call do_close(); in error case after post error messages into &SocketEventHandler::OnError. To sve order of coming messages.
//
//	2008-10-06
//	- Modify to use method post_error() everywhere where appricated.
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AsyncSocket.h"
#include "../HuSMPPClient.h"

#include "SMPP/States/SMPPSessionClosedState.h"

#include <boost/lexical_cast.hpp>
#include <boost/next_prior.hpp>

////////////////////////////////////////////////////////////

AsyncSocket::AsyncSocket(
	int ID,
	io_service_ptr io_service,
	boost::shared_ptr<SocketEventHandler> eventHandler,
	const std::string& sAddr,
	const std::string& sPort
	)
	    : strand_(*io_service), socket_(*io_service), m_nID(ID), m_EventHandler (eventHandler), isBinded_(false), disconnectInProgress_(false){
#ifdef DEBUG
lastCalledMethod = "Ctor";
#endif
boost::asio::ip::tcp::resolver resolver(strand_.get_io_service());

boost::asio::ip::tcp::resolver::query query(sAddr, sPort);
endpoint_iterator_ = resolver.resolve(query);

CH<ISMPPSessionClosedState> closedState; //? Initialization not needed???
m_SessionState = SafeCastCH<ISMPPSessionState, ISMPPSessionClosedState>( closedState );
}

////////////////////////////////////////////////////////
AsyncSocket::~AsyncSocket(){
#ifdef DEBUG
lastCalledMethod = "Dtor";
#endif
Close();
}

////////////////////////////////////////////////////////
void
AsyncSocket::Connect(){
#ifdef DEBUG
lastCalledMethod = "Connect()";
#endif
disconnectInProgress_ = false;

write_msgs_.clear(); //Clear queue
read_msg_.clear();

chASSERT( ! socket_.is_open() );
strand_.post(
	strand_.wrap(
		boost::bind(
			&AsyncSocket::do_connect,
			this
		)
	)
);
}

////////////////////////////////////////////////////////
void
AsyncSocket::Close(){
#ifdef DEBUG
lastCalledMethod = "Close()";
#endif
/* НЕ доходит?
	if (socket_.is_open()){
	strand_.post(
		strand_.wrap(
			boost::bind(
				&AsyncSocket::do_close,
				this
			)
		)
	);
	}
*/
do_close();
}

////////////////////////////////////////////////////////
void
AsyncSocket::do_close(){
#ifdef DEBUG
lastCalledMethod = "do_close()";
#endif

disconnectInProgress_ = true;

	if ( socket_.is_open() ){
	boost::system::error_code error;
	socket_.shutdown(boost::asio::socket_base::shutdown_both, error);

		if (error){
		post_error("Socket shutdown error!" + boost::lexical_cast<std::string>(error) + "; Message:" + error.message(), false);
		}
		else{
		socket_.close();
		isBinded_ = false;
		strand_.post(
			strand_.wrap(
				boost::bind(
					&SocketEventHandler::OnClose,
					m_EventHandler,
					m_nID
				)
			)
		);
		}
	}
}

////////////////////////////////////////////////////////
void
AsyncSocket::do_connect(){
#ifdef DEBUG
lastCalledMethod = "do_connect()";
#endif
boost::system::error_code error;
socket_.connect(*endpoint_iterator_, error);
handle_connect(error);
}

////////////////////////////////////////////////////////////
void
AsyncSocket::Write(const PDU_message& msg){
#ifdef DEBUG
lastCalledMethod = "Write(const PDU_message& msg)";
#endif
strand_.post(
	strand_.wrap(
		boost::bind(
			&AsyncSocket::do_write,
			this, //!!! Not shared_from_this()
			msg
		)
	)
);
}

////////////////////////////////////////////////////////
void
AsyncSocket::Write( CH<IRawBuffer> data ){
#ifdef DEBUG
lastCalledMethod = "Write( CH<IRawBuffer> data )";
#endif
//@todo Split to several chunks if greather
chASSERT( data->GetAvailableDataSize() <= PDU_message::max_body_length );
using namespace std; // For strlen and memcpy.
/**
* Incoming data has very similar structure to PDU_message.
* So, do NOT encode! All data sucsesfully encoded!
* Just fill raw data and fill length (not needed in shared_from_this() method, for consistent state
* if it will be used later)!
**/
PDU_message tmpMsg;
// body_length will be set in encode_header() which will be called automaticaly in setData()
//- tmpMsg.body_length( ntohl(  *(   ( PDU_message::LenType* )data->PeekData()   )  ) - sizeof(PDU_message::LenType) );
tmpMsg.setData(data->PeekData(), data->GetAvailableDataSize());
strand_.post(
//?	strand_.wrap(
		boost::bind(
			&AsyncSocket::do_write,
			this, //!!! Not shared_from_this()
			tmpMsg
		)
//	)
);
}

////////////////////////////////////////////////////////////
void
AsyncSocket::Write(
	const BYTE * buf,
	PDU_message::LenType bufLen //=0 Default 0 mean get strlen(buf)
	){
#ifdef DEBUG
lastCalledMethod = "Write(const BYTE * buf, PDU_message::LenType bufLen)";
#endif

/* WORK analogue:
CH<IRawBuffer> data;
bufLen = (bufLen ? bufLen : strlen((char*)buf));
DWORD t = htonl(bufLen + PDU_message::header_length);
data->AddData((BYTE *)(&t), sizeof(DWORD));
data->AddData(buf, bufLen);
return Write(data);
*/

using namespace std; // For strlen and memcpy.
PDU_message tmpMsg;
tmpMsg.setBody(buf, (bufLen ? bufLen : strlen((char*)buf)));
strand_.post(
//?	strand_.wrap( //With it is NOT work
		boost::bind(
			&AsyncSocket::do_write,
			this, //!!! Not shared_from_this()
			tmpMsg
		)
//	)
);
}

////////////////////////////////////////////////////////////
void
AsyncSocket::handle_connect(const boost::system::error_code& error){
#ifdef DEBUG
lastCalledMethod = "handle_connect(const boost::system::error_code& error)";
#endif

	if (!error){
	strand_.post(
		strand_.wrap(
			boost::bind(
				&SocketEventHandler::OnConnect,
				m_EventHandler,
				m_nID
			)
		)
	);

	boost::asio::async_read(
		socket_,
		boost::asio::buffer(
			read_msg_.data(),
			PDU_message::header_length
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_read_header,
				this,
				boost::asio::placeholders::error
			)
		)
	);
    }
	//http://www.solarix.ru/for_developers/cpp/boost/utility/ru/utility.shtml#functions_next_prior
    else if ( boost::next(endpoint_iterator_) != boost::asio::ip::tcp::resolver::iterator()){
	++endpoint_iterator_;
	socket_.close();
	do_connect(); //Try next server if exists
	}
	else{//Error
	post_error("Connect failed!" + boost::lexical_cast<std::string>(error) + "; Message:" + error.message());
	}
}

////////////////////////////////////////////////////////////
void
AsyncSocket::handle_read_header(const boost::system::error_code& error){
#ifdef DEBUG
lastCalledMethod = "handle_read_header(const boost::system::error_code& error)";
#endif

	if (!error && read_msg_.decode_header()){
	socket_.async_read_some(
		boost::asio::buffer(
			read_msg_.body(),
			read_msg_.body_length()
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_read_body,
				this,
				boost::asio::placeholders::error
			)
		)
	);
/*?1
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(
			read_msg_.body(),
			read_msg_.body_length()
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_read_body,
				this,
				boost::asio::placeholders::error
			)
		)
	);
*/
	}
	else{
	post_error("Error in handle_read_header! " + boost::lexical_cast<std::string>(error) + "; Message:" + error.message());
	}
}

////////////////////////////////////////////////////////////
void
AsyncSocket::handle_read_body(const boost::system::error_code& error){
#ifdef DEBUG
lastCalledMethod = "handle_read_body(const boost::system::error_code& error)";
#endif

	if (!error){
	socket_.async_read_some(
		boost::asio::buffer(
			read_msg_.data(),
			PDU_message::header_length
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_read_header,
				this,
				boost::asio::placeholders::error
			)
		)
	);
	/*?1
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(
			read_msg_.data(),
			PDU_message::header_length
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_read_header,
				this,
				boost::asio::placeholders::error
			)
		)
	);
	*/
	strand_.post(
		strand_.wrap(
			boost::bind(
				&SocketEventHandler::OnRead,
				m_EventHandler,
				read_msg_.getRawBuffer(),
				m_nID
			)
		)
	);
	}
	else{
	post_error("Read body failed!" + boost::lexical_cast<std::string>(error) + "; Message:" + error.message());
	}
}

////////////////////////////////////////////////////////////
void
AsyncSocket::do_write(PDU_message msg){
#ifdef DEBUG
lastCalledMethod = "do_write(PDU_message msg)";
#endif

bool write_in_progress = !write_msgs_.empty();
write_msgs_.push_back(msg);

	if (!write_in_progress){
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(
			write_msgs_.front().data(),
			write_msgs_.front().length()
		),
		strand_.wrap(
			boost::bind(
				&AsyncSocket::handle_write,
				this,
				boost::asio::placeholders::error
			)
		)
	);
	}
}

////////////////////////////////////////////////////////////
void
AsyncSocket::handle_write(const boost::system::error_code& error){
#ifdef DEBUG
lastCalledMethod = "handle_write(const boost::system::error_code& error)";
#endif

	if (!error){
		//This may be empty if errors accure and it was cleare in do_close()!
		if (!write_msgs_.empty()) write_msgs_.pop_front();

		if (!write_msgs_.empty()){
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(
				write_msgs_.front().data(),
				write_msgs_.front().length()
			),
			strand_.wrap(
				boost::bind(
					&AsyncSocket::handle_write,
					this,
					boost::asio::placeholders::error
				)
			)
		);

		strand_.post(
			strand_.wrap(
				boost::bind(
					&SocketEventHandler::OnWrite,
					m_EventHandler,
					write_msgs_.front().getRawBuffer(),
					m_nID
				)
			)
		);
		}
	}
	else{
	post_error("Write failed!" + boost::lexical_cast<std::string>(error) + "; Message:" + error.message());
	}
}

////////////////////////////////////////////////////////////
void
AsyncSocket::post_error(std::string errorMessage, bool doclose /* = true */){
	if (!disconnectInProgress_){//If not requested disconnect in effect!
	strand_.post(
		strand_.wrap(
			boost::bind(
			&SocketEventHandler::OnError,
			m_EventHandler,
			errorMessage,
			m_nID
			)
		)
	);
		if( doclose ) do_close();
	}
}