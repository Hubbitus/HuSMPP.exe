////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUParser.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-19
//	2008-07-19 - //91
//		Add in ParsePDU method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#include "../HuSMPPshared.h"
#include "../Utils/rawbuffer.h"

#include "PDUiterator.h"
#include "PDU.h"

////////////////////////////////////////////////////////

class IPDUParser{
public:
	virtual CH<IPDUIterator> ParsePDU( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ) = 0;

DECLARE_CH_REFCOUNTING( IPDUParser )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////