////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUDeliverSmResp.h
#pragma once

#ifndef __PDUDeliverSmResp_H__
#define __PDUDeliverSmResp_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDU.h"
////////////////////////////////////////////////////////
class IPDUDeliverSmResp : public IPDU
{
public:
  DECLARE_CH_REFCOUNTING( IPDUDeliverSmResp )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
