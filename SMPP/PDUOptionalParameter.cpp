////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameter.cpp
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../HuSMPPshared.h"

#include "SMPPSessionState.h"
#include "PDUOptionalParameter.h"

#include <vector>
#include <map>
using namespace std;

////////////////////////////////////////////////////////
class CPDUOptionalParameterImpl : public IPDUOptionalParameter{
public:
	CPDUOptionalParameterImpl();
	virtual ~CPDUOptionalParameterImpl();

	virtual void Initialize( CH<IRawBuffer> value ){};
	virtual void Initialize( std::string val ){};
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUOptionalParameter, CPDUOptionalParameterImpl )

////////////////////////////////////////////////////////
CPDUOptionalParameterImpl::CPDUOptionalParameterImpl()
{
}

////////////////////////////////////////////////////////
CPDUOptionalParameterImpl::~CPDUOptionalParameterImpl()
{
}

////////////////////////////////////////////////////////
// =================== END OF FILE =====================
////////////////////////////////////////////////////////