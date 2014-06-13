////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmRespFactory.h

#ifndef __PDUSubmitSmRespFACTORY_H__
#define __PDUSubmitSmRespFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUSubmitSmRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUSubmitSmRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
