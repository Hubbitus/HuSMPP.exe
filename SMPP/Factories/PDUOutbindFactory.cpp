////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOutbindFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-18
//	2008-07-18 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUOutbindFactory.h"
#include "../PDU/PDUOutbind.h"

////////////////////////////////////////////////////////

class CPDUOutbindFactoryImpl : public IPDUOutbindFactory{
public:
	CPDUOutbindFactoryImpl();
	virtual ~CPDUOutbindFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUOutbindFactory, CPDUOutbindFactoryImpl )

////////////////////////////////////////////////////////
CPDUOutbindFactoryImpl::CPDUOutbindFactoryImpl(){
}

////////////////////////////////////////////////////////
CPDUOutbindFactoryImpl::~CPDUOutbindFactoryImpl(){
}

////////////////////////////////////////////////////////
DWORD
CPDUOutbindFactoryImpl::GetId(){
return PDU_OUTBIND_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUOutbindFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUOutbind> retVal;

retVal->Initialize( rawBuffer, inSocket );
return SafeCastCH<IPDU, IPDUOutbind>( retVal );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////