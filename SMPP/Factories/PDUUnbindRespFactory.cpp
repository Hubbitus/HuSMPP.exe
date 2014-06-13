////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindRespFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUUnbindRespFactory.h"
#include "../PDU/PDUUnbindResp.h"

////////////////////////////////////////////////////////

class CPDUUnbindRespFactoryImpl : public IPDUUnbindRespFactory{
public:
	CPDUUnbindRespFactoryImpl();
	virtual ~CPDUUnbindRespFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUUnbindRespFactory, CPDUUnbindRespFactoryImpl )

////////////////////////////////////////////////////////
CPDUUnbindRespFactoryImpl::CPDUUnbindRespFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUUnbindRespFactoryImpl::~CPDUUnbindRespFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUUnbindRespFactoryImpl::GetId(){
return PDU_UNBIND_RESP_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUUnbindRespFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUUnbindResp> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUUnbindResp>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////