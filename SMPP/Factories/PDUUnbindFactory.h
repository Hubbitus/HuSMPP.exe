////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindFactory.h

#ifndef __PDUUnbindFACTORY_H__
#define __PDUUnbindFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUUnbindFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUUnbindFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
