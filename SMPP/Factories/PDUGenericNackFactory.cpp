////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUGenericNackFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUGenericNackFactory.h"
#include "../PDU/PDUGenericNack.h"

////////////////////////////////////////////////////////

class CPDUGenericNackFactoryImpl : public IPDUGenericNackFactory{
public:
	CPDUGenericNackFactoryImpl();
	virtual ~CPDUGenericNackFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUGenericNackFactory, CPDUGenericNackFactoryImpl )

////////////////////////////////////////////////////////
CPDUGenericNackFactoryImpl::CPDUGenericNackFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUGenericNackFactoryImpl::~CPDUGenericNackFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUGenericNackFactoryImpl::GetId(){
return PDU_GENERIC_NACK_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUGenericNackFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUGenericNack> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUGenericNack>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////