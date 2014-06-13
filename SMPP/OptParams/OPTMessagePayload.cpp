////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTMessagePayload.cpp
// Pavel Alexeev
// Created 2007-06-28 23:52
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTMessagePayload.h"

#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTMessagePayloadImpl : public OPTMessagePayload {
public:
	OPTMessagePayloadImpl();
	virtual ~OPTMessagePayloadImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( BYTE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTMessagePayload, OPTMessagePayloadImpl )

////////////////////////////////////////////////////////
OPTMessagePayloadImpl::OPTMessagePayloadImpl(){
}

////////////////////////////////////////////////////////
OPTMessagePayloadImpl::~OPTMessagePayloadImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTMessagePayloadImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
CH<IRawBuffer> retVal;
return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTMessagePayloadImpl::Initialize( CH<IRawBuffer> value ){
WORD length = ntohs(value->GetWORD());

m_Value->Clear();
m_Value->AddData(value->PeekData(), length);

//Для MessagePayload это Строка!
m_realValue = value->GetString(length);
}

////////////////////////////////////////////////////////
void
OPTMessagePayloadImpl::Initialize( std::string val ){
m_Value->Clear();

m_Value->AddData( (BYTE *) ( val.data() ), (WORD)val.length() );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTMessagePayloadImpl::Initialize( BYTE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = strUtils::WORD2str(val);
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////