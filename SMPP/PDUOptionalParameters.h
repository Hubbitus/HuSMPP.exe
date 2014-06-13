////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameters.h
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"
#include "../Utils/rawbuffer.h"

#include "PDUOptionalParameter.h"
#include "PDUOptionalParameterIterator.h"

#include "OptParams/OptFactory.h"
#include "OptParams/Factories/OptUnknownFactory.h"
#include "OptParams/Factories/OptDeliverRouteFactory.h"
#include "OptParams/Factories/OptUserResponseCodeFactory.h"
#include "OptParams/Factories/OptMessagePayloadFactory.h"

#include "OptParams/Factories/OptNetworkErrorCodeFactory.h"
#include "OptParams/Factories/OptMessageStateFactory.h"
#include "OptParams/Factories/OptReceiptedMessageIdFactory.h"

#include "OptParams/Factories/OptSourceSubaddressFactory.h"

#include "OptParams/Factories/OptSCInterfaceVersionFactory.h"
//+93
#include "OptParams/Factories/OptSarMsgRefNumFactory.h"
#include "OptParams/Factories/OptSarTotalSegmentsFactory.h"
#include "OptParams/Factories/OptSarSegmentSeqnumFactory.h"

#include <map>

////////////////////////////////////////////////////////

class IPDUOptionalParameters{
public:
	virtual void Initialize( CH<IRawBuffer> buffer ) =0;

	virtual CH<IPDUOptionalParameterIterator> GetParameters() =0;

	virtual CH<IPDUOptionalParameter> GetParameter( WORD parameterTagId ) =0;
	virtual void SetParameter( CH<IPDUOptionalParameter> param ) =0;

	//-47
	virtual CH<IRawBuffer> GetRawData() =0;
	//-47 Длина в байтах (Октетах) всех параметров, для сокета
	virtual WORD GetRawLength () =0;

	//+82
	virtual std::string GetString() =0;
protected:
	typedef map<WORD, CH<IPDUOptionalParameter> > OPTPARAMMAP;
	OPTPARAMMAP m_Parameters;

	//Фабрики
	typedef map<WORD, CH<IOptFactory> > OPTFactoryMAP;
	OPTFactoryMAP m_Factorys;

	//-47 Длина, для помещения в сокет
	WORD m_RawLength;

public:
  DECLARE_CH_REFCOUNTING( IPDUOptionalParameters )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////