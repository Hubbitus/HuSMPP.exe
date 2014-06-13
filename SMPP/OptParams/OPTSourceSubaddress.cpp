////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTSourceSubaddress.cpp
// Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTSourceSubaddress.h"

#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////

class OPTSourceSubaddressImpl : public OPTSourceSubaddress {
public:
	OPTSourceSubaddressImpl();
	virtual ~OPTSourceSubaddressImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( BYTE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTSourceSubaddress, OPTSourceSubaddressImpl )

////////////////////////////////////////////////////////
OPTSourceSubaddressImpl::OPTSourceSubaddressImpl(){
}

////////////////////////////////////////////////////////
OPTSourceSubaddressImpl::~OPTSourceSubaddressImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTSourceSubaddressImpl::GetRawData()
{
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTSourceSubaddressImpl::Initialize( CH<IRawBuffer> value ){
WORD length = ntohs(value->GetWORD());

m_Value->Clear();
m_Value->AddData(value->PeekData(), length);

m_realValue = value->GetString(length);
}

////////////////////////////////////////////////////////
void
OPTSourceSubaddressImpl::Initialize( std::string val ){
WORD length = (WORD)val.length();
m_Value->Clear();

m_Value->AddData( (BYTE *) ( val.c_str() ), length );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTSourceSubaddressImpl::Initialize( BYTE val ){
m_Value->Clear();
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = strUtils::WORD2str(val);
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////