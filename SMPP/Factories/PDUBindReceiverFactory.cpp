////////////////////////////////////////////////////////
// Project	: HuSMPP
// Module	: PDUBindReceiverFactory.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUBindReceiverFactory.h"
#include "../PDU/PDUBindReceiver.h"

////////////////////////////////////////////////////////

class CPDUBindReceiverFactoryImpl : public IPDUBindReceiverFactory{
public:
	CPDUBindReceiverFactoryImpl();
	virtual ~CPDUBindReceiverFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUBindReceiverFactory, CPDUBindReceiverFactoryImpl )

////////////////////////////////////////////////////////
CPDUBindReceiverFactoryImpl::CPDUBindReceiverFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUBindReceiverFactoryImpl::~CPDUBindReceiverFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUBindReceiverFactoryImpl::GetId(){
return PDU_BIND_RECEIVER_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUBindReceiverFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUBindReceiver> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUBindReceiver>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////