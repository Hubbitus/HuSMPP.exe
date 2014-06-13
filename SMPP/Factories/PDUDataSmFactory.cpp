////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDataSmFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUDataSmFactory.h"
#include "../PDU/PDUDataSm.h"

////////////////////////////////////////////////////////

class CPDUDataSmFactoryImpl : public IPDUDataSmFactory{
public:
	CPDUDataSmFactoryImpl();
	virtual ~CPDUDataSmFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUDataSmFactory, CPDUDataSmFactoryImpl )

////////////////////////////////////////////////////////
CPDUDataSmFactoryImpl::CPDUDataSmFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUDataSmFactoryImpl::~CPDUDataSmFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUDataSmFactoryImpl::GetId(){
return PDU_DATA_SM_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUDataSmFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUDataSm> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUDataSm>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////