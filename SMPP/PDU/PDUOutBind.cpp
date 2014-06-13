////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOutbind.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUOutbind.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUOutbindImpl : public IPDUOutbind{
public:
	CPDUOutbindImpl();
	virtual ~CPDUOutbindImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUOutbind, CPDUOutbindImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUOutbindImpl )

////////////////////////////////////////////////////////
CPDUOutbindImpl::CPDUOutbindImpl(){
}

////////////////////////////////////////////////////////
CPDUOutbindImpl::~CPDUOutbindImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUOutbindImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();

#pragma chMSG( Fix it later - add additional initialization )
}

////////////////////////////////////////////////////////
void
CPDUOutbindImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUOutbindImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUOutbindImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
CH<IRawBuffer> retVal;
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////