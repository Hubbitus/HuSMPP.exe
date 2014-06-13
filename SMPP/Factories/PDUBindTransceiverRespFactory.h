////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiverRespFactory.h

#ifndef __PDUBINDTRANSCEIVERRESPFACTORY_H__
#define __PDUBINDTRANSCEIVERRESPFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"

////////////////////////////////////////////////////////
class IPDUBindTransceiverRespFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUBindTransceiverRespFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
