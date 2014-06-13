////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTSCInterfaceVersion.cpp
// Pavel Alexeev	2008-01-15 09:22
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTSCInterfaceVersion.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTSCInterfaceVersionImpl : public OPTSCInterfaceVersion {
public:
	OPTSCInterfaceVersionImpl();
	virtual ~OPTSCInterfaceVersionImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( REALTYPE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTSCInterfaceVersion, OPTSCInterfaceVersionImpl )

////////////////////////////////////////////////////////
OPTSCInterfaceVersionImpl::OPTSCInterfaceVersionImpl(){
}

////////////////////////////////////////////////////////
OPTSCInterfaceVersionImpl::~OPTSCInterfaceVersionImpl(){
}

////////////////////////////////////////////////////////
void
OPTSCInterfaceVersionImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

m_realValue = value->GetBYTE();
}

////////////////////////////////////////////////////////
void
OPTSCInterfaceVersionImpl::Initialize( std::string val ){
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = (REALTYPE)strUtils::string2WORD(val);
}

////////////////////////////////////////////////////////
void
OPTSCInterfaceVersionImpl::Initialize( REALTYPE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = val;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////