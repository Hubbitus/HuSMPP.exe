////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : compositeaction.h

#ifndef __COMPOSITEACTION_H__
#define __COMPOSITEACTION_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/SMPPSessionState.h"
#include "action.h"
////////////////////////////////////////////////////////
class ICompositeAction : public IAction
{
public:
  virtual void AddAction( CH<IAction> ) = 0;

  DECLARE_CH_REFCOUNTING( ICompositeAction )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
