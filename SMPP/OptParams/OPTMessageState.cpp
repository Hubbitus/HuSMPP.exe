////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : OPTMessageState.cpp
// Pavel Alexeev	2007-11-29 02:15
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
//
//	2008-09-03
//	- OPTMessageStateImpl::Initialize( std::string val ) implementation changed
//		from simplify treat string value as decimal to thread string value as
//		one of string representation of state.
//
//	2008-09-09
//	- Add text value for UNDEFINED
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../../HuSMPPshared.h"
#include "../PDUOptionalParameter.h"
#include "OPTMessageState.h"

////////////////////////////////////////////////////////
class OPTMessageStateImpl : public OPTMessageState {
public:
	OPTMessageStateImpl();
	virtual ~OPTMessageStateImpl();

	virtual void Initialize( CH<IRawBuffer> value );
	virtual void Initialize( std::string val );
	virtual void Initialize( REALTYPE val );

	virtual std::string GetSymbolicName( char state  = -1);

private:
	void initSymbNames();
	std::map<REALTYPE, std::string> mutable SymbNames_;

	bool initializedSymbNames;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( OPTMessageState, OPTMessageStateImpl )

////////////////////////////////////////////////////////
OPTMessageStateImpl::OPTMessageStateImpl()
	: initializedSymbNames(false){
m_realValue = OPTMessageState::UNDEFINED;
}

////////////////////////////////////////////////////////
OPTMessageStateImpl::~OPTMessageStateImpl(){
}

/*-82
////////////////////////////////////////////////////////
CH<IRawBuffer>
OPTMessageStateImpl::GetRawData(){
#pragma chMSG( Fix it later - correct buffer initialization )
  CH<IRawBuffer> retVal;
  return retVal;
}
*/

////////////////////////////////////////////////////////
void
OPTMessageStateImpl::Initialize( CH<IRawBuffer> value ){
m_Value->Clear();
m_Value->AddData(value->PeekData(), ntohs(value->GetWORD()));

m_realValue = value->GetBYTE();
}

////////////////////////////////////////////////////////
void
OPTMessageStateImpl::Initialize( std::string val ){
//m_Value->AddData( (BYTE *) ( val.c_str() ), (WORD)val.length() );
//m_realValue = strUtils::string2WORD(val);

//Initialisation on demand
initSymbNames();
std::map<REALTYPE, std::string>::const_iterator fI = SymbNames_.begin();
	//Direct each compare
	while (fI != SymbNames_.end() && fI->second != val){
	++fI;
	}

	if (fI != SymbNames_.end()){
	m_realValue = fI->first;
	}
	else{
	m_realValue = UNDEFINED;
	}

Initialize(m_realValue);
}

////////////////////////////////////////////////////////
void
OPTMessageStateImpl::Initialize( REALTYPE val ){
m_Value->AddData( (BYTE *) ( &val ), sizeof(val) );

m_realValue = val;
}

////////////////////////////////////////////////////////
void
OPTMessageStateImpl::initSymbNames(){
	if (initializedSymbNames) return;
/*
	SymbNames[SCHEDULED]		= "SCHEDULED";
	SymbNames[ENROUTE]			= "ENROUTE";
	SymbNames[DELIVERED]		= "DELIVERED";
	SymbNames[EXPIRED]			= "EXPIRED";
	SymbNames[DELETED]			= "DELETED";
	SymbNames[UNDELIVERABLE]	= "UNDELIVERABLE";
	SymbNames[ACCEPTED]			= "ACCEPTED";
	SymbNames[UNKNOWN]			= "UNKNOWN";
	SymbNames[REJECTED]			= "REJECTED";
	SymbNames[SKIPPED]			= "SKIPPED";
*/
	SymbNames_[UNDEFINED]		= "_UNDEFINED_";//+Hu

	SymbNames_[SCHEDULED]		= "SCHEDULED";
	SymbNames_[ENROUTE]			= "ENROUTE";
	SymbNames_[DELIVERED]		= "DELIVRD";
	SymbNames_[EXPIRED]			= "EXPIRED";
	SymbNames_[DELETED]			= "DELETED";
	SymbNames_[UNDELIVERABLE]	= "UNDELIV";
	SymbNames_[ACCEPTED]		= "ACCEPTD";
	SymbNames_[UNKNOWN]			= "UNKNOWN";
	SymbNames_[REJECTED]		= "REJECTD";
	SymbNames_[SKIPPED]			= "SKIPPED";
	initializedSymbNames = true;	//Once
	}

////////////////////////////////////////////////////////
std::string
OPTMessageStateImpl::GetSymbolicName( char state /*= -1*/) {
//Initialisation on demand
initSymbNames();

	if ( state != -1) return SymbNames_[state];
	else{
/*	BYTE t = *m_Value->PeekData();
	std::string ret = SymbNames[t];
	return ret;
*/
	return SymbNames_[GetRealValue()];
	}
}