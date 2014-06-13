////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: PDU_message.cpp
// Author	: Pavel Alexeev (aka Pahan-Hubbitus)
// Created	: 1008-09-23 18:17 (create CPP to separate implementation from hpp)
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PDU_message.h"

////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <cstring>

////////////////////////////////////////////////////////
PDU_message::PDU_message() : body_length_(0){
}

////////////////////////////////////////////////////////
PDU_message::~PDU_message(){
}

////////////////////////////////////////////////////////
/*
void
PDU_message::body_length(LenType length){
body_length_ = length;
	if (body_length_ > max_body_length)
	body_length_ = max_body_length;
}
*/

////////////////////////////////////////////////////////
bool
PDU_message::decode_header(){
body_length_ = ntohl(  *(   ( LenType* )data_   )  ) - header_length;
	
	if (body_length_ > max_body_length){
	body_length_ = 0;
	//? return false;
	throw new std::exception("Net buffer overflow!!!");
	}
return true;
}

////////////////////////////////////////////////////////
void
PDU_message::encode_header(){
LenType tmpLen = htonl(body_length_ + header_length);
memcpy(data_, &tmpLen, header_length);
}

////////////////////////////////////////////////////////
CH<IRawBuffer> 
PDU_message::getRawBuffer(){
CH<IRawBuffer> retBuf;
retBuf->AddData( (BYTE*)data(), (int)length());
return retBuf;
}

////////////////////////////////////////////////////////
void
PDU_message::setData (const BYTE* from, size_t len){
	if ( len > max_body_length + header_length ){
	throw new std::exception("Net buffer overflow!!!");
	}
memcpy((void *)data(), from, len);
body_length_ = len - header_length;

chASSERT(body_length_ == ntohl(  *(   ( PDU_message::LenType* )from   )  ) - header_length);
}

////////////////////////////////////////////////////////
void
PDU_message::setBody (const BYTE* from, size_t len){
	if ( len > max_body_length ){
	throw new std::exception("Net buffer overflow!!!");
	}
memcpy((void *)body(), from, len);
body_length_ = len;

encode_header();
chASSERT(body_length_ == ntohl(  *(   ( PDU_message::LenType* )data()   )  ) - header_length);
}

////////////////////////////////////////////////////////
void
PDU_message::clear(){
body_length_ = 0;
}