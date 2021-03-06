////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnbindResp.h
#pragma once

#ifndef __PDUUnbindResp_H__
#define __PDUUnbindResp_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDU.h"
////////////////////////////////////////////////////////

class IPDUUnbindResp : public IPDU
{
public:
  DECLARE_CH_REFCOUNTING( IPDUUnbindResp )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
