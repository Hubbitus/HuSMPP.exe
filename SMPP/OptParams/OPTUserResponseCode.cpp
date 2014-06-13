////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTUserResponseCode.cpp
// Pavel Alexeev
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTUserResponseCode.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTUserResponseCodeImpl : public OPTUserResponseCode {
public:
	OPTUserResponseCodeImpl();
	virtual ~OPTUserResponseCodeImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( BYTE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTUserResponseCode, OPTUserResponseCodeImpl )

////////////////////////////////////////////////////////
OPTUserResponseCodeImpl::OPTUserResponseCodeImpl(){
}

////////////////////////////////////////////////////////
OPTUserResponseCodeImpl::~OPTUserResponseCodeImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTUserResponseCodeImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTUserResponseCodeImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

//Для user_response_code это BYTE!
m_realValue = value->GetBYTE();
//--???	m_realValue = ntohs (m_realValue);
}

////////////////////////////////////////////////////////
//-47 My
void
OPTUserResponseCodeImpl::Initialize( std::string val ){
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

//!
m_realValue = strUtils::string2WORD(val);
}

////////////////////////////////////////////////////////
//-47 My
void
OPTUserResponseCodeImpl::Initialize( BYTE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = val;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////