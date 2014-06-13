////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarTotalSegments.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTSarTotalSegments.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTSarTotalSegmentsImpl : public OPTSarTotalSegments {
public:
	OPTSarTotalSegmentsImpl();
	virtual ~OPTSarTotalSegmentsImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( REALTYPE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTSarTotalSegments, OPTSarTotalSegmentsImpl )

////////////////////////////////////////////////////////
OPTSarTotalSegmentsImpl::OPTSarTotalSegmentsImpl(){
}

////////////////////////////////////////////////////////
OPTSarTotalSegmentsImpl::~OPTSarTotalSegmentsImpl(){
}

////////////////////////////////////////////////////////
void
OPTSarTotalSegmentsImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

m_realValue = value->GetBYTE();
}

////////////////////////////////////////////////////////
void
OPTSarTotalSegmentsImpl::Initialize( std::string val ){
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = (REALTYPE)strUtils::string2WORD(val);
}

////////////////////////////////////////////////////////
void
OPTSarTotalSegmentsImpl::Initialize( REALTYPE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = val;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////