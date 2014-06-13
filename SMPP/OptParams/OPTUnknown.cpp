////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : OPTUnknown.cpp
// Pavel Alexeev
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTUnknown.h"
#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTUnknownImpl : public OPTUnknown {
public:
	OPTUnknownImpl();
	virtual ~OPTUnknownImpl();

	virtual void Initialize( CH<IRawBuffer> value );
//	virtual void Initialize( std::string val );
	virtual void Initialize( REALTYPE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTUnknown, OPTUnknownImpl )

////////////////////////////////////////////////////////
OPTUnknownImpl::OPTUnknownImpl(){
}

////////////////////////////////////////////////////////
OPTUnknownImpl::~OPTUnknownImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTUnknownImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTUnknownImpl::Initialize( CH<IRawBuffer> value ){
WORD length = ntohs(value->GetWORD());

	//-73
	if (length > value->GetAvailableDataSize()) length = (WORD)value->GetAvailableDataSize();

//Скопируем и УДАЛИМ (извлечем) из переданного буфера то что относится к данному параметру
m_Value->Clear();
m_Value->AddData(value->PeekData(), length);

//Для Unknown просто пропустим!
//m_realValue = value->Skip(m_Length);
value->Skip(length);
}

////////////////////////////////////////////////////////
/*85
void
OPTUnknownImpl::Initialize( std::string val ){
m_Value->Clear();
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTUnknownImpl::Initialize( REALTYPE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = (REALTYPE)strUtils::WORD2str(val);
}
*/
void
OPTUnknownImpl::Initialize( REALTYPE val ){
m_Value->Clear();
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = val;
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////