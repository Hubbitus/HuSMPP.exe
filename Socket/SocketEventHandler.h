////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SocketEventHandler.h
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-15
////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////
#include "../Utils/rawbuffer.h"
////////////////////////////////////////////////////////
class SocketEventHandler{
public:
	virtual void OnRead( const CH<IRawBuffer> data, const int SocketID ) = 0;
	virtual void OnWrite( const CH<IRawBuffer> data, const int SocketID ) = 0;
	virtual void OnConnect( const int SocketID ) = 0;
	virtual void OnClose( const int SocketID ) = 0;

	virtual void OnError( const std::string& description, const int SocketID ) = 0;
};