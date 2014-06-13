////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameters.cpp
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-12-07
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../Common/CmnHdr.h"

#include "SMPPSessionState.h"
#include "PDUOptionalParameters.h"

////////////////////////////////////////////////////////

#include <vector>
#include <map>

////////////////////////////////////////////////////////
class CPDUOptionalParametersImpl : public IPDUOptionalParameters{
public:
  CPDUOptionalParametersImpl();
  virtual ~CPDUOptionalParametersImpl();

  virtual void Initialize( CH<IRawBuffer> buffer );

  virtual CH<IPDUOptionalParameterIterator> GetParameters();
  virtual CH<IPDUOptionalParameter> GetParameter( WORD parameterTagId );
  virtual void SetParameter( CH<IPDUOptionalParameter> param );

	//-47
	virtual CH<IRawBuffer> GetRawData();
	virtual WORD GetRawLength ();
	//+My
	void AddFactory ( CH<IOptFactory> factory );

	//+82
	std::string GetString();
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IPDUOptionalParameters, CPDUOptionalParametersImpl )

void
CPDUOptionalParametersImpl::AddFactory ( CH<IOptFactory> factory )
{
  m_Factorys[ factory->GetTagId() ] = factory;
}

////////////////////////////////////////////////////////
CPDUOptionalParametersImpl::CPDUOptionalParametersImpl(){
m_RawLength = 0; //Ноль сначала
	
//-44 Добавление Опциональных Параметров
CH<IOptUnknownFactory> OPTUnknownFactory;
AddFactory( SafeCastCH<IOptFactory, IOptUnknownFactory>( OPTUnknownFactory ) );

CH<IOptUserResponseCodeFactory> OPTUserResponseCodeFactory;
AddFactory( SafeCastCH<IOptFactory, IOptUserResponseCodeFactory>( OPTUserResponseCodeFactory ) );

CH<IOptDeliverRouteFactory> OPTDeliverRouteFactory;
AddFactory( SafeCastCH<IOptFactory, IOptDeliverRouteFactory>( OPTDeliverRouteFactory ) );

CH<IOptMessagePayloadFactory> OPTMessagePayloadFactory;
AddFactory( SafeCastCH<IOptFactory, IOptMessagePayloadFactory>( OPTMessagePayloadFactory ) );

//+79 4 more
CH<IOptNetworkErrorCodeFactory> OPTNetworkErrorCodeFactory;
AddFactory( SafeCastCH<IOptFactory, IOptNetworkErrorCodeFactory>( OPTNetworkErrorCodeFactory ) );

CH<IOptMessageStateFactory> OPTMessageStateFactory;
AddFactory( SafeCastCH<IOptFactory, IOptMessageStateFactory>( OPTMessageStateFactory ) );

CH<IOptReceiptedMessageIdFactory> OPTReceiptedMessageIdFactory;
AddFactory( SafeCastCH<IOptFactory, IOptReceiptedMessageIdFactory>( OPTReceiptedMessageIdFactory ) );

CH<IOptSourceSubaddressFactory> OPTSourceSubaddressFactory;
AddFactory( SafeCastCH<IOptFactory, IOptSourceSubaddressFactory>( OPTSourceSubaddressFactory ) );


CH<IOptSCInterfaceVersionFactory> OPTSCInterfaceVersionFactory;
AddFactory( SafeCastCH<IOptFactory, IOptSCInterfaceVersionFactory>( OPTSCInterfaceVersionFactory ) );

//+93 3 more
CH<IOptSarMsgRefNumFactory> OPTSarMsgRefNumFactory;
AddFactory( SafeCastCH<IOptFactory, IOptSarMsgRefNumFactory>( OPTSarMsgRefNumFactory ) );

CH<IOptSarTotalSegmentsFactory> OPTSarTotalSegmentsFactory;
AddFactory( SafeCastCH<IOptFactory, IOptSarTotalSegmentsFactory>( OPTSarTotalSegmentsFactory ) );

CH<IOptSarSegmentSeqnumFactory> OPTSarSegmentSeqnumFactory;
AddFactory( SafeCastCH<IOptFactory, IOptSarSegmentSeqnumFactory>( OPTSarSegmentSeqnumFactory ) );
}

////////////////////////////////////////////////////////
CPDUOptionalParametersImpl::~CPDUOptionalParametersImpl()
{
m_Parameters.clear();
m_Factorys.clear();
}

////////////////////////////////////////////////////////
void
CPDUOptionalParametersImpl::Initialize( CH<IRawBuffer> buffer ){
int BuffLen = buffer->GetAvailableDataSize();

 	while (BuffLen > 0){
	WORD ParamTagID = ntohs(buffer->GetWORD());

	//Ищем Factory в списке, если находим...
    OPTFactoryMAP::const_iterator optIter = m_Factorys.find( ParamTagID );
	CH<IOptFactory> optFactory;
	CH<IPDUOptionalParameter> optParam;
		if ( optIter != m_Factorys.end() ){
		//..то optFactory указывает на нужный Factory уже
		optFactory = optIter->second;
		optParam = optFactory->Make(buffer);
		}
		else{
		optFactory = m_Factorys[PDU_OPT_UNKNOWN];//Он полюбому там должен быть
		optParam = optFactory->Make(buffer);//Только для Unknown нужно передавать TagID
		SafeDynamicCastCH<OPTUnknown,IPDUOptionalParameter>(optParam)->SetTagId(ParamTagID);
		}

	SetParameter(optParam);
	//Ну и уменьшаем длину буфера
	BuffLen -= (
		sizeof(WORD)			//Длина ID тега
		+ sizeof(WORD)			//Длина длины
		+ optParam->GetLength()	//Сами данные
	);
	chASSERT(BuffLen >= 0);
	}
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameterIterator>
CPDUOptionalParametersImpl::GetParameters(){
  CH<IPDUOptionalParameterIterator> retVal;

  for ( OPTPARAMMAP::iterator iter = m_Parameters.begin(); iter != m_Parameters.end(); iter++ )
    retVal->PutOptParam( iter->second );

  return retVal;
}

////////////////////////////////////////////////////////
CH<IPDUOptionalParameter>
CPDUOptionalParametersImpl::GetParameter( WORD parameterTagId )
{
/*-47
  CH<IPDUOptionalParameter> retVal = m_Parameters[ parameterTagId ];
  return retVal;
*/

//-47 +My
//Ищем Factory в списке, если находим...
    OPTPARAMMAP::const_iterator paramIter = m_Parameters.find( parameterTagId );
	CH<IOptFactory> optFactory;
		if ( paramIter != m_Parameters.end() ) return paramIter->second;
		else{//Иначе он неизвестный
		CH<OPTUnknown> unKnown;
		unKnown->Initialize(std::string("ParameterUnknown"));
		//И просто возвращаем, ничего вставлять в параметры не надо
		return SafeCastCH<IPDUOptionalParameter, OPTUnknown>(unKnown);
		}
}

////////////////////////////////////////////////////////
//+My
void
CPDUOptionalParametersImpl::SetParameter( CH<IPDUOptionalParameter> param )
{
//param должен быть уже инициализированным!
m_Parameters[ param->GetTagId() ] = param; 

#pragma chMSG( "Fix it later. Обработать ситуацию когда он уже был, и изменяется, а не добавляется!" )
	//увеличение общей длины
	m_RawLength += (
					sizeof(WORD)//Длина ID тега
					+ sizeof(WORD)//Длина длины
					+ param->GetLength() //Сами данные
					);
}

////////////////////////////////////////////////////////
CH<IRawBuffer> CPDUOptionalParametersImpl::GetRawData(){
CH<IRawBuffer> retVal;
//Итерируем по каждому:
CH<IPDUOptionalParameterIterator> optIter = GetParameters();
	while (optIter->More()){
	retVal->AddData(
		optIter->Next()->GetRawData()->PeekData()
		,(optIter->Peek()->GetLength() + sizeof(WORD)/*Tag*/ + sizeof(WORD)/*Length*/)
	);
	}

return retVal;
}

////////////////////////////////////////////////////////
std::string CPDUOptionalParametersImpl::GetString(){
std::ostringstream retVal ("OptParams:");
//Итерируем по каждому:
CH<IPDUOptionalParameterIterator> optIter = GetParameters();
	while (optIter->More()){
	retVal << "[" << optIter->Next()->GetTagId() << "]" << optIter->Peek()->operator std::string() << ENDLINE;
	}

return retVal.str();
}

////////////////////////////////////////////////////////
//-47
WORD
CPDUOptionalParametersImpl::GetRawLength (){
return m_RawLength;
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////