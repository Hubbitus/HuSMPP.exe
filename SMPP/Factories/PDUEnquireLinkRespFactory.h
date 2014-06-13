////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUEnquireLinkRespFactory.h

#ifndef __PDUENQUIRELINKRESPFACTORY_H__
#define __PDUENQUIRELINKRESPFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUEnquireLinkRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUEnquireLinkRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
