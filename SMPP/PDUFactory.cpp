////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUFactory.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../HuSMPPshared.h"

#include "SMPPSessionState.h"
#include "PDUFactory.h"

////////////////////////////////////////////////////////
// CPDUFactoryImpl class
class CPDUFactoryImpl : public IPDUFactory{
public:
	CPDUFactoryImpl();
	virtual ~CPDUFactoryImpl();

	virtual DWORD GetId();
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUFactory, CPDUFactoryImpl )

////////////////////////////////////////////////////////
CPDUFactoryImpl::CPDUFactoryImpl()
{
}

////////////////////////////////////////////////////////
CPDUFactoryImpl::~CPDUFactoryImpl()
{
}

////////////////////////////////////////////////////////
DWORD
CPDUFactoryImpl::GetId()
{
  return PDU_INVALID_ID;
}

////////////////////////////////////////////////////////
CH<IPDU>
CPDUFactoryImpl::Make( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDU> retVal;

retVal->Initialize( rawBuffer, inSocket );
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
