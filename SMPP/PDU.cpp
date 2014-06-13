////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDU.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PDU.h"

////////////////////////////////////////////////////////

class CPDUBasicImpl : public IPDU{
public:
	CPDUBasicImpl();
	virtual ~CPDUBasicImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	//+My add
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){};
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){};

	virtual CH<IRawBuffer> GetRawData();

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDU, CPDUBasicImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION_VIRTUAL_STUB( CPDUBasicImpl )

////////////////////////////////////////////////////////
CPDUBasicImpl::CPDUBasicImpl(){
}

////////////////////////////////////////////////////////
CPDUBasicImpl::~CPDUBasicImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUBasicImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
}

////////////////////////////////////////////////////////
CH<IAction>
CPDUBasicImpl::ProcessState(){
#pragma chMSG( Fix it later )
CH<INullAction> retVal;
retVal->Initialize();

return ( SafeCastCH<IAction, INullAction>( retVal ) );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUBasicImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
CH<IRawBuffer> retVal;
return retVal;
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////