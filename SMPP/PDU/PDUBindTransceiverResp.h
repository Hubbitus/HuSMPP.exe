////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUBindTranceiverResp.h
#pragma once

#ifndef __PDUBINDTRANCEIVERRESP_H__
#define __PDUBINDTRANCEIVERRESP_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include <string>

#include "../PDU.h"
////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////
class IPDUBindTransceiverResp : public IPDU
{
public:
  virtual void SetSystemId( const char* system_id ) = 0;
  virtual const string& GetSystemId() = 0;

  DECLARE_CH_REFCOUNTING( IPDUBindTransceiverResp )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
