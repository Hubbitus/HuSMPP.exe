////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUFactory.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Make method boost::shared_ptr<AsyncSocket> inSocket patrameter due to
//		process realisation of abbility working with 2 sockets
////////////////////////////////////////////////////////

#ifndef __PDUFACTORY_H__
#define __PDUFACTORY_H__

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"

#include "PDU.h"
#include "../Utils/rawbuffer.h"

////////////////////////////////////////////////////////
class IPDUFactory
{
public:
	virtual DWORD GetId() = 0;
	virtual CH<IPDU> Make( CH<IRawBuffer>, boost::shared_ptr<AsyncSocket> inSocket ) = 0;

DECLARE_CH_REFCOUNTING( IPDUFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////