////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOutbind.h
#pragma once

#ifndef __PDUOUTBIND_H__
#define __PDUOUTBIND_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDU.h"
////////////////////////////////////////////////////////

class IPDUOutbind : public IPDU
{
public:
  DECLARE_CH_REFCOUNTING( IPDUOutbind )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
