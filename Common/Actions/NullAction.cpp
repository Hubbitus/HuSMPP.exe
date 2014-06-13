////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : nullaction.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-17
//	2008-07-17 - //91
//	-	Remove from Perform method second unneded parameter: CH<ISMPPSessionState> currentState.
//		It is now accessed "by pdu->getInSocket()->getSessionState()" if needed.
//	-	Accordingly remove method GetNewState() and also CH<ISMPPSessionState> m_NewState; member
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "nullaction.h"

////////////////////////////////////////////////////////

class CNullActionImpl : public INullAction{
public:
  CNullActionImpl();
  virtual ~CNullActionImpl();

  virtual void Initialize();

  virtual CH<ISMPPSessionState> Perform( CH<IPDU> pdu );
  virtual CH<IPDU> GetResponse();

};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( INullAction, CNullActionImpl )

////////////////////////////////////////////////////////
CNullActionImpl::CNullActionImpl(){
}

////////////////////////////////////////////////////////
CNullActionImpl::~CNullActionImpl(){
}

////////////////////////////////////////////////////////
void 
CNullActionImpl::Initialize(){
}

////////////////////////////////////////////////////////
CH<ISMPPSessionState>
CNullActionImpl::Perform( CH<IPDU> pdu ){
//AsIs
return pdu->GetInSocket()->getSessionState();
}

////////////////////////////////////////////////////////
CH<IPDU>
CNullActionImpl::GetResponse(){
CH<IPDU> retVal;
return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////