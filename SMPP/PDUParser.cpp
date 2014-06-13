////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUParser.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in ParsePDU method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../HuSMPPshared.h"
#include "SMPPSessionState.h"

#include "PDUParser.h"
#include "PDUIterator.h"

#include "PDUFactory.h"
#include "Factories/PDUBindTransceiverFactory.h"
#include "Factories/PDUBindTransceiverRespFactory.h"
//+91+4
#include "Factories/PDUBindReceiverFactory.h"
#include "Factories/PDUBindReceiverRespFactory.h"
#include "Factories/PDUBindTransmitterFactory.h"
#include "Factories/PDUBindTransmitterRespFactory.h"
#include "Factories/PDUEnquireLinkFactory.h"
#include "Factories/PDUEnquireLinkRespFactory.h"
#include "Factories/PDUGenericNackFactory.h"
#include "Factories/PDUOutbindFactory.h"
#include "Factories/PDUUnknownFactory.h"

#include "Factories/PDUUnbindFactory.h"
#include "Factories/PDUUnbindRespFactory.h"
#include "Factories/PDUSubmitSmFactory.h"
#include "Factories/PDUSubmitSmRespFactory.h"
#include "Factories/PDUDeliverSmFactory.h"
#include "Factories/PDUDeliverSmRespFactory.h"
#include "Factories/PDUDataSmFactory.h"
#include "Factories/PDUDataSmRespFactory.h"

////////////////////////////////////////////////////////

#include <map>

////////////////////////////////////////////////////////

class CPDUParserImpl : public IPDUParser{
public:
	CPDUParserImpl();
	virtual ~CPDUParserImpl();

	virtual CH<IPDUIterator> ParsePDU( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket );
private:
	typedef std::map<DWORD, CH<IPDUFactory> > FACTORYMAP;
	FACTORYMAP m_Factories;

	CH<IPDUFactory> m_MiscFactory;

	inline void AddFactory( CH<IPDUFactory> factory );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUParser, CPDUParserImpl )

////////////////////////////////////////////////////////
CPDUParserImpl::CPDUParserImpl(){
CH<IPDUBindTransceiverFactory> bindTransceiverFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindTransceiverFactory>( bindTransceiverFactory ) );

CH<IPDUBindTransceiverRespFactory> bindTransceiverRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindTransceiverRespFactory>( bindTransceiverRespFactory ) );

//+91+11
CH<IPDUBindReceiverFactory> bindReceiverFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindReceiverFactory>( bindReceiverFactory ) );

CH<IPDUBindReceiverRespFactory> bindReceiverRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindReceiverRespFactory>( bindReceiverRespFactory ) );

CH<IPDUBindTransmitterFactory> bindTransmitterFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindTransmitterFactory>( bindTransmitterFactory ) );

CH<IPDUBindTransmitterRespFactory> bindTransmitterRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUBindTransmitterRespFactory>( bindTransmitterRespFactory ) );

CH<IPDUEnquireLinkFactory> enquireLinkFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUEnquireLinkFactory>( enquireLinkFactory ) );

CH<IPDUEnquireLinkRespFactory> enquireLinkRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUEnquireLinkRespFactory>( enquireLinkRespFactory ) );

CH<IPDUGenericNackFactory> genericNackFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUGenericNackFactory>( genericNackFactory ) );

CH<IPDUOutbindFactory> outbindFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUOutbindFactory>( outbindFactory ) );

CH<IPDUUnbindFactory> unbindFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUUnbindFactory> ( unbindFactory ) );

CH<IPDUUnbindRespFactory> unbindRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUUnbindRespFactory> ( unbindRespFactory ) );

CH<IPDUSubmitSmFactory> submitSmFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUSubmitSmFactory> ( submitSmFactory ) );

CH<IPDUSubmitSmRespFactory> submitSmRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUSubmitSmRespFactory> ( submitSmRespFactory ) );

CH<IPDUDeliverSmFactory> deliverSmFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUDeliverSmFactory> ( deliverSmFactory ) );

CH<IPDUDeliverSmRespFactory> deliverSmRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUDeliverSmRespFactory> ( deliverSmRespFactory ) );

CH<IPDUDataSmFactory> dataSmFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUDataSmFactory> ( dataSmFactory ) );

CH<IPDUDataSmRespFactory> dataSmRespFactory;
AddFactory( SafeCastCH<IPDUFactory, IPDUDataSmRespFactory> ( dataSmRespFactory ) );

CH<IPDUUnknownFactory> unknownFactory;
m_MiscFactory = SafeCastCH<IPDUFactory, IPDUUnknownFactory>( unknownFactory );
}
 
////////////////////////////////////////////////////////
CPDUParserImpl::~CPDUParserImpl(){
m_Factories.clear();
}

////////////////////////////////////////////////////////
inline void 
CPDUParserImpl::AddFactory( CH<IPDUFactory> factory ){
m_Factories[ factory->GetId() ] = factory;
}

////////////////////////////////////////////////////////
CH<IPDUIterator>
CPDUParserImpl::ParsePDU( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ){
CH<IPDUIterator> retVal;

	for(;;){
	unsigned int avSize = rawBuffer->GetAvailableDataSize();

		if ( avSize < sizeof( PDUHeader ) ) break;

	PDUHeader *hdr;
	hdr = ( PDUHeader* ) rawBuffer->PeekData();

	PDUHeader newHeader = *hdr;
	newHeader.NTOH();

	unsigned int requestSize = ( newHeader.command_length );

		if ( avSize < requestSize ) break;

	//—начала Unknown
	CH<IPDUFactory> pduFactory = m_MiscFactory;

	//»щем Factory в списке, если находим...
	FACTORYMAP::iterator pduIter = m_Factories.find( newHeader.command_id );
		if ( pduIter != m_Factories.end() )
		//..то pduFactory указывает на нужный Factory уже
		pduFactory = pduIter->second;

	CH<IRawBuffer> requestBuffer;

    requestBuffer->AddData( rawBuffer->PeekData(), requestSize );
    CH<IPDU> pdu = pduFactory->Make( requestBuffer, inSocket );

    retVal->PutPDU( pdu );

    rawBuffer->Skip( requestSize );
	}

return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////