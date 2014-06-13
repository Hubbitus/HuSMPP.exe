////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiverFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindTransceiverFactory.h"
#include "../PDU/PDUBindTransceiver.h"

////////////////////////////////////////////////////////

class CPDUBindTransceiverFactoryImpl : public IPDUBindTransceiverFactory{
public:
	CPDUBindTransceiverFactoryImpl();
	virtual ~CPDUBindTransceiverFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindTransceiverFactory, CPDUBindTransceiverFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindTransceiverFactoryImpl::CPDUBindTransceiverFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindTransceiverFactoryImpl::~CPDUBindTransceiverFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindTransceiverFactoryImpl::GetId(){
return PDU_BIND_TRANSCEIVER_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindTransceiverFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindTransceiver> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindTransceiver>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////