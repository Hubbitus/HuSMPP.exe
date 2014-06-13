////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUUnknown.h
#pragma once

#ifndef __PDUUNKNOWN_H__
#define __PDUUNKNOWN_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "../PDU.h"

/*-52
#include "../SMPPSessionState.h"
/////////////Temp
*/
////////////////////////////////////////////////////////

class IPDUUnknown : public IPDU{
public:
  DECLARE_CH_REFCOUNTING( IPDUUnknown )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
