////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUSubmitSmRespFactory.h"
#include "../PDU/PDUSubmitSmResp.h"

////////////////////////////////////////////////////////

class CPDUSubmitSmRespFactoryImpl : public IPDUSubmitSmRespFactory{
public:
	CPDUSubmitSmRespFactoryImpl();
	virtual ~CPDUSubmitSmRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUSubmitSmRespFactory, CPDUSubmitSmRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUSubmitSmRespFactoryImpl::CPDUSubmitSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUSubmitSmRespFactoryImpl::~CPDUSubmitSmRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUSubmitSmRespFactoryImpl::GetId(){
return PDU_SUBMIT_SM_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUSubmitSmRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUSubmitSmResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUSubmitSmResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////