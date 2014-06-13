////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDataSmRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDataSmRespFactory.h"
#include "../PDU/PDUDataSmResp.h"

////////////////////////////////////////////////////////

class CPDUDataSmRespFactoryImpl : public IPDUDataSmRespFactory{
public:
	CPDUDataSmRespFactoryImpl();
	virtual ~CPDUDataSmRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDataSmRespFactory, CPDUDataSmRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUDataSmRespFactoryImpl::CPDUDataSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUDataSmRespFactoryImpl::~CPDUDataSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUDataSmRespFactoryImpl::GetId(){
return PDU_DATA_SM_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUDataSmRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUDataSmResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUDataSmResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////