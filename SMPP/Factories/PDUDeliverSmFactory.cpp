////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDeliverSmFactory.h"
#include "../PDU/PDUDeliverSm.h"

////////////////////////////////////////////////////////

class CPDUDeliverSmFactoryImpl : public IPDUDeliverSmFactory{
public:
	CPDUDeliverSmFactoryImpl();
	virtual ~CPDUDeliverSmFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDeliverSmFactory, CPDUDeliverSmFactoryImpl )

////////////////////////////////////////////////////////
CPDUDeliverSmFactoryImpl::CPDUDeliverSmFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUDeliverSmFactoryImpl::~CPDUDeliverSmFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUDeliverSmFactoryImpl::GetId(){
return PDU_DELIVER_SM_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUDeliverSmFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUDeliverSm> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUDeliverSm>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////