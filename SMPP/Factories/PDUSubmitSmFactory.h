////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmFactory.h

#ifndef __PDUSubmitSmFACTORY_H__
#define __PDUSubmitSmFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUSubmitSmFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUSubmitSmFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
