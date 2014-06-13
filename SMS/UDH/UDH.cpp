////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : UDH.h
// Pavel Alexeev
// Created 2007-06-27 15:08
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UDH.h"

////////////////////////////////////////////////////////

class CUDHImpl : public IUDH{
public:
	CUDHImpl();
	virtual ~CUDHImpl();

	virtual void Initialize( CH<IRawBuffer> buffer );

	virtual CH<IIEsIterator> GetIEs();
	virtual CH<IIE> GetIE ( WORD IEI );
	virtual void SetIE( CH<IIE> IEI );

	virtual CH<IRawBuffer> GetRawData();
	virtual WORD GetRawLength();

	void AddFactory ( CH<IIEFactory> factory );
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IUDH, CUDHImpl )

void
CUDHImpl::AddFactory ( CH<IIEFactory> factory ){
m_Factorys[ factory->GetIEI() ] = factory;
}

////////////////////////////////////////////////////////
CUDHImpl::CUDHImpl(){
m_RawLength = 0; //Ноль сначала
	
//Добавление различных известных IE здесь
CH<IIEUnknownFactory> IEUnknownFactory;
AddFactory( SafeCastCH<IIEFactory, IIEUnknownFactory>( IEUnknownFactory ) );

CH<IIEConcatenatedFactory> IEConcatenatedFactory;
AddFactory( SafeCastCH<IIEFactory, IIEConcatenatedFactory>( IEConcatenatedFactory ) );

CH<IIEConcatenated_longFactory> IEConcatenated_longFactory;
AddFactory( SafeCastCH<IIEFactory, IIEConcatenated_longFactory>( IEConcatenated_longFactory ) );	
}

////////////////////////////////////////////////////////
CUDHImpl::~CUDHImpl(){
m_IEs.clear();
m_Factorys.clear();
}

////////////////////////////////////////////////////////
void
CUDHImpl::Initialize( CH<IRawBuffer> buffer ){
unsigned int BuffLen = buffer->GetAvailableDataSize();

	while (BuffLen > 0){
	WORD IEI = ntohs( *((BYTE *)buffer->PeekData())); //IE Identifier

	//Ищем Factory в списке, если находим...
    IEsFactoryMAP::const_iterator IEIter = m_Factorys.find( IEI );
	CH<IIEFactory> IEFactory;
		if ( IEIter != m_Factorys.end() )
		//..то IEFactory указывает на нужный Factory уже
		IEFactory = IEIter->second;
		else IEFactory = m_Factorys[UDH_IE_unknown];//Он полюбому там должен быть

	CH<IIE> ie = IEFactory->Make(buffer);
	SetIE (ie);
	//Ну и уменьшаем длину буфера
	BuffLen -= ie->GetLength(); //Длина IE
	}
}

////////////////////////////////////////////////////////
CH<IIEsIterator>
CUDHImpl::GetIEs(){
	CH<IIEsIterator> retVal;

	for ( IEsMAP::const_iterator iter = m_IEs.begin(); iter != m_IEs.end(); iter++ )
	retVal->PutIE( iter->second );

return retVal;
}

////////////////////////////////////////////////////////
CH<IIE>
CUDHImpl::GetIE( WORD IEI ){
//Ищем Factory в списке, если находим...
IEsMAP::const_iterator IEsIter = m_IEs.find( IEI );
CH<IIEFactory> IEFactory;
	if ( IEsIter != m_IEs.end() ) return IEsIter->second;
	else{//Иначе он неизвестный
	CH<IEUnknown> unKnown;
	//И просто возвращаем, ничего вставлять в параметры не надо
	return SafeCastCH<IIE, IEUnknown>(unKnown);
	}
}

////////////////////////////////////////////////////////
void
CUDHImpl::SetIE( CH<IIE> ie ){
m_IEs[ ie->GetIEI() ] = ie;

#pragma chMSG( "CUDHImpl::SetIE:: Fix it later. Обработать ситуацию когда он уже был, и изменяется, а не добавляется!" )
//увеличение общей длины
#pragma warning(push)
#pragma warning(disable:4244)
m_RawLength += ie->GetLength(); //Длина IE
#pragma warning(pop)
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CUDHImpl::GetRawData(){
CH<IRawBuffer> retVal;

//Итерируем по каждому:
CH<IIEsIterator> IEsIter = GetIEs();
	while (IEsIter->More()){
	CH<IIE> ie = IEsIter->Next();
	retVal->AddData(ie->GetRawData()->PeekData(), ie->GetRawData()->GetAvailableDataSize());
	}

return retVal;
}

////////////////////////////////////////////////////////
WORD
CUDHImpl::GetRawLength(){
return m_RawLength;
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////