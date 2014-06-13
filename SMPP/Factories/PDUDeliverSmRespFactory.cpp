////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDeliverSmRespFactory.h"
#include "../PDU/PDUDeliverSmResp.h"

////////////////////////////////////////////////////////

class CPDUDeliverSmRespFactoryImpl : public IPDUDeliverSmRespFactory{
public:
	CPDUDeliverSmRespFactoryImpl();
	virtual ~CPDUDeliverSmRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDeliverSmRespFactory, CPDUDeliverSmRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUDeliverSmRespFactoryImpl::CPDUDeliverSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUDeliverSmRespFactoryImpl::~CPDUDeliverSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUDeliverSmRespFactoryImpl::GetId(){
return PDU_DELIVER_SM_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUDeliverSmRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUDeliverSmResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUDeliverSmResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////