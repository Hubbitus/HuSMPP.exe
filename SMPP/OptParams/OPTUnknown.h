////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTUnknown.h
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class OPTUnknown : public IPDUOptionalParameter{
public:
	//Additions for Unknown. Primarly for Logs and debugging
	virtual WORD GetTagId () const {return m_TagID;};
	virtual void SetTagId (WORD tagID) {m_TagID = tagID;};
protected:
	WORD m_TagID;

OPT_BASICS_DECLARATION(std::string, PDU_OPT_UNKNOWN)
DECLARE_CH_REFCOUNTING( OPTUnknown )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////