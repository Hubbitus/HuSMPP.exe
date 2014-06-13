////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: PDU_message.h
// Author	: Pavel Alexeev (aka Pahan-Hubbitus)
//
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../Utils/RawBuffer.h"

////////////////////////////////////////////////////////

class PDU_message{
public:
	typedef DWORD LenType;

	enum { header_length = sizeof(LenType) };
    enum { max_body_length = (64 * 1024 - header_length) };

	PDU_message();
	~PDU_message();

	LenType length() const { return header_length + body_length_; };
	LenType body_length() const { return body_length_; };
//	void body_length(LenType length);

	void setData (const BYTE* from, size_t len);
	void setBody (const BYTE* from, size_t len);

	bool decode_header();
	void encode_header();

	void clear();

	CH<IRawBuffer> getRawBuffer();
	char * data(){
	return data_;
	};
	char * body(){
	return data_ + header_length;
	};

private:
	char data_[header_length + max_body_length];
	LenType body_length_;
};
