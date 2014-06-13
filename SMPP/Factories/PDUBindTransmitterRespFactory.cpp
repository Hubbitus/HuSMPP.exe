////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindTransmitterRespFactory.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransmitterRespFactory.h"
#include "../PDU/PDUBindTransmitterResp.h"

////////////////////////////////////////////////////////

class CPDUBindTransmitterRespFactoryImpl : public IPDUBindTransmitterRespFactory{
public:
	CPDUBindTransmitterRespFactoryImpl();
	virtual ~CPDUBindTransmitterRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransmitterRespFactory, CPDUBindTransmitterRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindTransmitterRespFactoryImpl::CPDUBindTransmitterRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindTransmitterRespFactoryImpl::~CPDUBindTransmitterRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindTransmitterRespFactoryImpl::GetId(){
return PDU_BIND_TRANSMITTER_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindTransmitterRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindTransmitterResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindTransmitterResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////