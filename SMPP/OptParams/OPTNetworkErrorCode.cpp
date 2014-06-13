////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTNetworkErrorCode.cpp
// Pavel Alexeev	2007-11-29 02:15
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTNetworkErrorCode.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTNetworkErrorCodeImpl : public OPTNetworkErrorCode {
public:
	OPTNetworkErrorCodeImpl();
	virtual ~OPTNetworkErrorCodeImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( DWORD val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTNetworkErrorCode, OPTNetworkErrorCodeImpl )

////////////////////////////////////////////////////////
OPTNetworkErrorCodeImpl::OPTNetworkErrorCodeImpl(){
}

////////////////////////////////////////////////////////
OPTNetworkErrorCodeImpl::~OPTNetworkErrorCodeImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTNetworkErrorCodeImpl::GetRawData(){

CH<IRawBuffer> retVal;

WORD tmp = 0;//Neccesary, because ->AddData Необходимо, потому что берется указатель
tmp = htons (defaultTagID);
retVal->AddData( (BYTE *) (&tmp), sizeof(WORD)); //Добавляем TagID
tmp = htons (m_Length);
retVal->AddData( (BYTE *) (&tmp), sizeof(WORD));
retVal->AddData( GetValue()->PeekData(), GetLength() );

return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTNetworkErrorCodeImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

//это 3 Bytes!!
//DO NOT working directly. Why?? So, using addon variable...
//m_realValue = (value->GetBYTE() << 16) + value->GetWORD();
BYTE code = value->GetBYTE();
m_realValue = (code << 16) + value->GetWORD();
}

////////////////////////////////////////////////////////
void
OPTNetworkErrorCodeImpl::Initialize( std::string val ){
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = (val[0] << 16) + (val[1] << 8) + val[2];
}

////////////////////////////////////////////////////////
void
OPTNetworkErrorCodeImpl::Initialize( DWORD val ){
m_realValue = val;

//3 Bytes!!!
//m_Value->AddData( (BYTE *) ( &(val << 8) ), 3 );
val <<= 8;
m_Value->AddData( (BYTE *) ( &val ), 3 );
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////