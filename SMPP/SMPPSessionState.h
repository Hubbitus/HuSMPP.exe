////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMPPSessionState.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-21
//	2008-07-19 //91.1
//		Add processing of IPDUCache
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"
#include "PDU.h"

#include "../Common/Actions/action.h"

////////////////////////////////////////////////////////

class ISMPPSessionState{
public:
	virtual void Initialize() = 0;

	virtual const char* GetClassName() = 0;

	virtual CH<IAction> Process( SP<IPDUUnknown> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUBindTransceiver> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUBindTransceiverResp> pdu ) = 0;
	//+90+4
	virtual CH<IAction> Process( SP<IPDUBindReceiver> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUBindReceiverResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUBindTransmitter> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUBindTransmitterResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUEnquireLink> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUEnquireLinkResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUGenericNack> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUOutbind> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUUnbind> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUUnbindResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUSubmitSm> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUSubmitSmResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUDeliverSm> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUDeliverSmResp> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUDataSm> pdu ) = 0;
	virtual CH<IAction> Process( SP<IPDUDataSmResp> pdu ) = 0;
	//+91.1
	virtual CH<IAction> Process( SP<IPDUCache> pdu ) = 0;
DECLARE_CH_REFCOUNTING( ISMPPSessionState )
};

////////////////////////////////////////////////////////
#define SMPP_SESSION_STATE_BASICS_DECLARATION \
public: \
	virtual const char* GetClassName() { return m_ClassName; } \
	virtual CH<IAction> Process( SP<IPDUUnknown> pdu ); \
	virtual CH<IAction> Process( SP<IPDUBindTransceiver> pdu ); \
	virtual CH<IAction> Process( SP<IPDUBindTransceiverResp> pdu ); \
	/*+90+4 */ \
	virtual CH<IAction> Process( SP<IPDUBindReceiver> pdu ); \
	virtual CH<IAction> Process( SP<IPDUBindReceiverResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUBindTransmitter> pdu ); \
	virtual CH<IAction> Process( SP<IPDUBindTransmitterResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUEnquireLink> pdu ); \
	virtual CH<IAction> Process( SP<IPDUEnquireLinkResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUGenericNack> pdu ); \
	virtual CH<IAction> Process( SP<IPDUOutbind> pdu ); \
	virtual CH<IAction> Process( SP<IPDUUnbind> pdu ); \
	virtual CH<IAction> Process( SP<IPDUUnbindResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUSubmitSm> pdu ); \
	virtual CH<IAction> Process( SP<IPDUSubmitSmResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUDeliverSm> pdu ); \
	virtual CH<IAction> Process( SP<IPDUDeliverSmResp> pdu ); \
	virtual CH<IAction> Process( SP<IPDUDataSm> pdu ); \
	virtual CH<IAction> Process( SP<IPDUDataSmResp> pdu ); \
	/* +91.1 */ \
	virtual CH<IAction> Process( SP<IPDUCache> pdu ); \
private: \
	static const char m_ClassName[]; \


////////////////////////////////////////////////////////
#define SMPP_SESSION_STATE_BASICS_DEFINITION( Type ) \
	const char Type::m_ClassName[] = #Type; \


////////////////////////////////////////////////////////
#define SMPP_SESSION_STATE_EMPTY_HANDLER_DEFINITION( StateInterface, StateType, PduType ) \
CH<IAction> StateType::Process( SP<PduType> pdu ) \
{ \
CH<INullAction> retVal; \
retVal->Initialize(); \
return ( SafeCastCH<IAction, INullAction>( retVal ) ); \
} \

// =================== END OF FILE =====================
////////////////////////////////////////////////////////