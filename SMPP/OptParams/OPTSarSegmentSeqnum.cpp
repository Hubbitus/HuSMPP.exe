////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: OPTSarSegmentSeqnum.cpp
// Author	: Pavel Alexeev
// Created	: 2008-08-20 14:49
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTSarSegmentSeqnum.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTSarSegmentSeqnumImpl : public OPTSarSegmentSeqnum {
public:
	OPTSarSegmentSeqnumImpl();
	virtual ~OPTSarSegmentSeqnumImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( REALTYPE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTSarSegmentSeqnum, OPTSarSegmentSeqnumImpl )

////////////////////////////////////////////////////////
OPTSarSegmentSeqnumImpl::OPTSarSegmentSeqnumImpl(){
}

////////////////////////////////////////////////////////
OPTSarSegmentSeqnumImpl::~OPTSarSegmentSeqnumImpl(){
}

////////////////////////////////////////////////////////
void
OPTSarSegmentSeqnumImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

m_realValue = value->GetBYTE();
}

////////////////////////////////////////////////////////
void
OPTSarSegmentSeqnumImpl::Initialize( std::string val ){
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = (REALTYPE)strUtils::string2WORD(val);
}

////////////////////////////////////////////////////////
void
OPTSarSegmentSeqnumImpl::Initialize( REALTYPE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = val;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////