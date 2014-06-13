////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUSubmitSmResp.h
#pragma once

#ifndef __PDUSubmitSmResp_H__
#define __PDUSubmitSmResp_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../PDU.h"
////////////////////////////////////////////////////////

class IPDUSubmitSmResp : public IPDU
{
public:
  //
  virtual void SetMessageId( const char* message_id ) = 0;
  virtual const string& GetMessageId() = 0;

  DECLARE_CH_REFCOUNTING( IPDUSubmitSmResp )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
