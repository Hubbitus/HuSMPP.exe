////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindTransmitterFactory.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransmitterFactory.h"
#include "../PDU/PDUBindTransmitter.h"

////////////////////////////////////////////////////////

class CPDUBindTransmitterFactoryImpl : public IPDUBindTransmitterFactory{
public:
	CPDUBindTransmitterFactoryImpl();
	virtual ~CPDUBindTransmitterFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransmitterFactory, CPDUBindTransmitterFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindTransmitterFactoryImpl::CPDUBindTransmitterFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindTransmitterFactoryImpl::~CPDUBindTransmitterFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindTransmitterFactoryImpl::GetId(){
return PDU_BIND_TRANSMITTER_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindTransmitterFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindTransmitter> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindTransmitter>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////