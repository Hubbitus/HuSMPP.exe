////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnknownFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUUnknownFactory.h"
#include "../PDU/PDUUnknown.h"

class CPDUUnknownFactoryImpl : public IPDUUnknownFactory{
public:
	CPDUUnknownFactoryImpl();
	virtual ~CPDUUnknownFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUUnknownFactory, CPDUUnknownFactoryImpl )

////////////////////////////////////////////////////////
CPDUUnknownFactoryImpl::CPDUUnknownFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUUnknownFactoryImpl::~CPDUUnknownFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUUnknownFactoryImpl::GetId(){
return PDU_UNKNOWN_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUUnknownFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUUnknown> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUUnknown>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////