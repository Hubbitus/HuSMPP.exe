////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindResp.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PDUUnbindResp.h"
#include "../SMPPSessionState.h"

////////////////////////////////////////////////////////

class CPDUUnbindRespImpl : public IPDUUnbindResp{
public:
	CPDUUnbindRespImpl();
	virtual ~CPDUUnbindRespImpl();

	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
	virtual CH<IRawBuffer> GetRawData();

PDU_BASICS_DECLARATION
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUUnbindResp, CPDUUnbindRespImpl )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUUnbindRespImpl )

////////////////////////////////////////////////////////
CPDUUnbindRespImpl::CPDUUnbindRespImpl(){
m_Header.command_status = ESME_ROK;
m_Header.command_id = PDU_UNBIND_RESP_ID;
}

////////////////////////////////////////////////////////
CPDUUnbindRespImpl::~CPDUUnbindRespImpl(){
}

////////////////////////////////////////////////////////
void 
CPDUUnbindRespImpl::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;
	
unsigned int offset = 0;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();
offset += sizeof( m_Header );
chASSERT( offset <= m_Header.command_length );
rawBuffer->Skip( sizeof( m_Header ) );
}

////////////////////////////////////////////////////////
void
CPDUUnbindRespImpl::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerIn ( this );
}

////////////////////////////////////////////////////////
void
CPDUUnbindRespImpl::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
EventHandler->OnPDUEventHandlerOut ( this );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUUnbindRespImpl::GetRawData(){
CH<IRawBuffer> retVal;

m_Header.command_length = sizeof( m_Header );
m_Header.command_id = PDU_UNBIND_RESP_ID;

m_Header.HTON();
retVal->AddData( ( BYTE* )( &m_Header ), sizeof( m_Header ) );
m_Header.NTOH();

return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////