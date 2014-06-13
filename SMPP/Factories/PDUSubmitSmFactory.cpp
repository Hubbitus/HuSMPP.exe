////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUSubmitSmFactory.h"
#include "../PDU/PDUSubmitSm.h"

////////////////////////////////////////////////////////

class CPDUSubmitSmFactoryImpl : public IPDUSubmitSmFactory{
public:
	CPDUSubmitSmFactoryImpl();
	virtual ~CPDUSubmitSmFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUSubmitSmFactory, CPDUSubmitSmFactoryImpl )

////////////////////////////////////////////////////////
CPDUSubmitSmFactoryImpl::CPDUSubmitSmFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUSubmitSmFactoryImpl::~CPDUSubmitSmFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUSubmitSmFactoryImpl::GetId(){
return PDU_SUBMIT_SM_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUSubmitSmFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUSubmitSm> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUSubmitSm>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////