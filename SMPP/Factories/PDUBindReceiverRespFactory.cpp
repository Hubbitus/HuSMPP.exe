////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindReceiverRespFactory.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindReceiverRespFactory.h"
#include "../PDU/PDUBindReceiverResp.h"

////////////////////////////////////////////////////////

class CPDUBindReceiverRespFactoryImpl : public IPDUBindReceiverRespFactory{
public:
	CPDUBindReceiverRespFactoryImpl();
	virtual ~CPDUBindReceiverRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindReceiverRespFactory, CPDUBindReceiverRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindReceiverRespFactoryImpl::CPDUBindReceiverRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindReceiverRespFactoryImpl::~CPDUBindReceiverRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindReceiverRespFactoryImpl::GetId(){
return PDU_BIND_RECEIVER_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindReceiverRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindReceiverResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindReceiverResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////