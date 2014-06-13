////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMSCache.h
// Modifyed by Pavel Alexeev
// Для обмена через виндовые мессаги
// Modifyed by Pavel Alexeev 2008-05-19
////////////////////////////////////////////////////////

#ifndef __SMSCache_H__
#define __SMSCache_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/PDUCache.h"
#include "../../SMPP/PDU.h"
#include "../../SMPP/PDUIterator.h"
////////////////////////////////////////////////////////
class ISMSCache{
public:
	virtual void Initialize() = 0;

	//-61
	virtual void AddPDU( CH<IPDUCache> pdu ) = 0;
	virtual void AddPDU( CH<IPDU> pdu ) = 0;
	virtual CH<IPDUIterator> GetAllCachedPDUs() = 0;

DECLARE_CH_REFCOUNTING( ISMSCache )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////