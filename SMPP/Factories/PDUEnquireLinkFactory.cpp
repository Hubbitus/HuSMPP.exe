////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUEnquireLinkFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUEnquireLinkFactory.h"
#include "../PDU/PDUEnquireLink.h"

////////////////////////////////////////////////////////

class CPDUEnquireLinkFactoryImpl : public IPDUEnquireLinkFactory{
public:
	CPDUEnquireLinkFactoryImpl();
	virtual ~CPDUEnquireLinkFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUEnquireLinkFactory, CPDUEnquireLinkFactoryImpl )

////////////////////////////////////////////////////////
CPDUEnquireLinkFactoryImpl::CPDUEnquireLinkFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUEnquireLinkFactoryImpl::~CPDUEnquireLinkFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUEnquireLinkFactoryImpl::GetId(){
return PDU_ENQUIRE_LINK_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUEnquireLinkFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUEnquireLink> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUEnquireLink>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////