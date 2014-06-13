////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTSourceSubaddress.h
// Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"

////////////////////////////////////////////////////////
class OPTSourceSubaddress : public IPDUOptionalParameter{
public:
	enum { NSAP_EVEN_ITUT_X_213 = 0x80, NSAP_ODD_ITUT_X_213 = 88, User_Specified = 0xA0 };

	//Type of Subaddress tag - TOST :)
	BYTE GetTOST(){
		if (m_realValue.length() > 0) return m_realValue[0];
		else return 0;
	};

	std::string	GetSubaddress(){
		if (m_realValue.length() > 0) return m_realValue.substr(1);
		else return "";
	};

OPT_BASICS_DECLARATION(std::string, PDU_OPT_SourceSubaddress)
DECLARE_CH_REFCOUNTING( OPTSourceSubaddress )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////