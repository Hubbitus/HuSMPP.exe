////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUEnquireLinkRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUEnquireLinkRespFactory.h"
#include "../PDU/PDUEnquireLinkResp.h"

////////////////////////////////////////////////////////

class CPDUEnquireLinkRespFactoryImpl : public IPDUEnquireLinkRespFactory{
public:
	CPDUEnquireLinkRespFactoryImpl();
	virtual ~CPDUEnquireLinkRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUEnquireLinkRespFactory, CPDUEnquireLinkRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUEnquireLinkRespFactoryImpl::CPDUEnquireLinkRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUEnquireLinkRespFactoryImpl::~CPDUEnquireLinkRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUEnquireLinkRespFactoryImpl::GetId(){
return PDU_ENQUIRE_LINK_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUEnquireLinkRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUEnquireLinkResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUEnquireLinkResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////