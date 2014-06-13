////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTDeliverRoute.cpp
// Pavel Alexeev
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTDeliverRoute.h"

#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////

class OPTDeliverRouteImpl : public OPTDeliverRoute {
public:
	OPTDeliverRouteImpl();
	virtual ~OPTDeliverRouteImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( BYTE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTDeliverRoute, OPTDeliverRouteImpl )

////////////////////////////////////////////////////////
OPTDeliverRouteImpl::OPTDeliverRouteImpl(){
}

////////////////////////////////////////////////////////
OPTDeliverRouteImpl::~OPTDeliverRouteImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTDeliverRouteImpl::GetRawData()
{
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTDeliverRouteImpl::Initialize( CH<IRawBuffer> value ){
WORD length = ntohs(value->GetWORD());

m_Value->Clear();
m_Value->AddData(value->PeekData(), length);
	
m_realValue = value->GetString(length);
}

////////////////////////////////////////////////////////
void
OPTDeliverRouteImpl::Initialize( std::string val ){
WORD length = (WORD)val.length();
m_Value->Clear();

m_Value->AddData( (BYTE *) ( val.c_str() ), length );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTDeliverRouteImpl::Initialize( BYTE val ){
m_Value->Clear();
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = strUtils::WORD2str(val);
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////