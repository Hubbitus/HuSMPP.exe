////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : nullaction.h

#ifndef __NULLACTION_H__
#define __NULLACTION_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"
#include "action.h"
/*-52
#include "../../SMPP/SMPPSessionState.h"
*/
////////////////////////////////////////////////////////
class INullAction : public IAction
{
public:
  DECLARE_CH_REFCOUNTING( INullAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
