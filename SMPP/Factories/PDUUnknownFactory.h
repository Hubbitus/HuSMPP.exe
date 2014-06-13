////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnknownFactory.h

#ifndef __PDUUNKNOWNFACTORY_H__
#define __PDUUNKNOWNFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUUnknownFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUUnknownFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
