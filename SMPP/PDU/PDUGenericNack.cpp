////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUGenericNack.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUGenericNack.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUGenericNackImpl : public IPDUGenericNack{
public:
	CPDUGenericNackImpl();
	virtual ~CPDUGenericNackImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUGenericNack, CPDUGenericNackImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUGenericNackImpl )

////////////////////////////////////////////////////////
CPDUGenericNackImpl::CPDUGenericNackImpl(){
}

////////////////////////////////////////////////////////
CPDUGenericNackImpl::~CPDUGenericNackImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUGenericNackImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();

#pragma chMSG( Fix it later - add additional initialization )
}

////////////////////////////////////////////////////////
void
CPDUGenericNackImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUGenericNackImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUGenericNackImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
CH<IRawBuffer> retVal;
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////