////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUUnbindFactory.h"
#include "../PDU/PDUUnbind.h"

////////////////////////////////////////////////////////

class CPDUUnbindFactoryImpl : public IPDUUnbindFactory{
public:
	CPDUUnbindFactoryImpl();
	virtual ~CPDUUnbindFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUUnbindFactory, CPDUUnbindFactoryImpl )

////////////////////////////////////////////////////////
CPDUUnbindFactoryImpl::CPDUUnbindFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUUnbindFactoryImpl::~CPDUUnbindFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUUnbindFactoryImpl::GetId(){
return PDU_UNBIND_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUUnbindFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUUnbind> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUUnbind>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////