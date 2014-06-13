////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUEnquireLinkResp.h
#pragma once

#ifndef __PDUENQUIRELINKRESP_H__
#define __PDUENQUIRELINKRESP_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDU.h"
////////////////////////////////////////////////////////

class IPDUEnquireLinkResp : public IPDU
{
public:
  DECLARE_CH_REFCOUNTING( IPDUEnquireLinkResp )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
