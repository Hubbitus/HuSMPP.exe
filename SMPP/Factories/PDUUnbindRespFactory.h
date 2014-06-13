////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindRespFactory.h

#ifndef __PDUUnbindRespFACTORY_H__
#define __PDUUnbindRespFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUUnbindRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUUnbindRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
