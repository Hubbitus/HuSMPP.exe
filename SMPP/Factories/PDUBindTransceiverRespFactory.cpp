////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiverRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransceiverRespFactory.h"
#include "../PDU/PDUBindTransceiverResp.h"

////////////////////////////////////////////////////////

class CPDUBindTransceiverRespFactoryImpl : public IPDUBindTransceiverRespFactory{
public:
	CPDUBindTransceiverRespFactoryImpl();
	virtual ~CPDUBindTransceiverRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransceiverRespFactory, CPDUBindTransceiverRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindTransceiverRespFactoryImpl::CPDUBindTransceiverRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindTransceiverRespFactoryImpl::~CPDUBindTransceiverRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindTransceiverRespFactoryImpl::GetId(){
return PDU_BIND_TRANSCEIVER_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindTransceiverRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindTransceiverResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindTransceiverResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////