////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : PDUCache.cpp
// Pavel Alexeev
////////////////////////////////////////////////////////

#pragma once
#include "pdu.h"

class IPDUCache : public IPDU {
private:
	int IncomingID;
	int OutcomingID;

DECLARE_CH_REFCOUNTING( IPDUCache )
};
