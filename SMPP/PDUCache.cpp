////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : PDUCache.cpp
// Pavel Alexeev
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete implementation of method ProcessState, because it is now in macroses PDU_BASICS_DECLARATION and PDU_BASICS_DEFINITION
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PDUCache.h"

class CPDUCache : public IPDUCache {
public:
	CPDUCache(void) : IncomingID (-1), OutcomingID (-1){};
	virtual ~CPDUCache(void);
	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
	virtual CH<IRawBuffer> GetRawData();

	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler );
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler );
private:
	int IncomingID;
	int OutcomingID;

PDU_BASICS_DECLARATION	
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUCache, CPDUCache )

////////////////////////////////////////////////////////
PDU_BASICS_DEFINITION( CPDUCache )

////////////////////////////////////////////////////////

CPDUCache::~CPDUCache(void){
}

////////////////////////////////////////////////////////
void 
CPDUCache::Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
m_pSocket = inSocket;

PDUHeader *hdr;
hdr = ( PDUHeader * ) rawBuffer->PeekData();
m_Header = *hdr;
m_Header.NTOH();

#pragma chMSG( Fix it later - add additional initialization )
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CPDUCache::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
CH<IRawBuffer> retVal;
return retVal;
}

////////////////////////////////////////////////////////
/*-91
CH<IAction>
CPDUCache::ProcessState(){
//Ёто не надо в  еше
//  return state->Process( this );
CH<INullAction> retVal;
return SafeCastCH<IAction, INullAction> (retVal);
}
*/

////////////////////////////////////////////////////////
void
CPDUCache::ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ){
//"Ёто не надо в  еше"
//	EventHandler->OnPDUEventHandler ( this );
}

////////////////////////////////////////////////////////
void
CPDUCache::ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ){
//#pragma chMSG( "Ёто не надо в  еше" )
}