////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTReceiptedMessageId.cpp
// Pavel Alexeev	2007-11-29 15:36
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTReceiptedMessageId.h"

#include "../../Utils/stringUtils.h"

////////////////////////////////////////////////////////
class OPTReceiptedMessageIdImpl : public OPTReceiptedMessageId{
public:
	OPTReceiptedMessageIdImpl();
	virtual ~OPTReceiptedMessageIdImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( BYTE val );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTReceiptedMessageId, OPTReceiptedMessageIdImpl )

////////////////////////////////////////////////////////
OPTReceiptedMessageIdImpl::OPTReceiptedMessageIdImpl(){
}

////////////////////////////////////////////////////////
OPTReceiptedMessageIdImpl::~OPTReceiptedMessageIdImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTReceiptedMessageIdImpl::GetRawData()
{
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTReceiptedMessageIdImpl::Initialize( CH<IRawBuffer> value ){
WORD length = ntohs(value->GetWORD());

m_Value->Clear();
m_Value->AddData(value->PeekData(), length);

//Для ReceiptedMessageId это Строка!
m_realValue = value->GetCString(length);
}

////////////////////////////////////////////////////////
void
OPTReceiptedMessageIdImpl::Initialize( std::string val ){
m_Value->Clear();
m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTReceiptedMessageIdImpl::Initialize( BYTE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = strUtils::WORD2str(val);
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////