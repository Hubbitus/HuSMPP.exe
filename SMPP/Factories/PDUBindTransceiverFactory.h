////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTransceiverFactory.h

#ifndef __PDUBINDTRANSCEIVERFACTORY_H__
#define __PDUBINDTRANSCEIVERFACTORY_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDUFactory.h"
////////////////////////////////////////////////////////

class IPDUBindTransceiverFactory : public IPDUFactory
{
public:

  DECLARE_CH_REFCOUNTING( IPDUBindTransceiverFactory )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
