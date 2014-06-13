////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUEnquireLinkFactory.h

#ifndef __PDUENQUIRELINKFACTORY_H__
#define __PDUENQUIRELINKFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUEnquireLinkFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUEnquireLinkFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
