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
m_RawLength = 0; //���� �������
	
//���������� ��������� ��������� IE �����
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

	//���� Factory � ������, ���� �������...
    IEsFactoryMAP::const_iterator IEIter = m_Factorys.find( IEI );
	CH<IIEFactory> IEFactory;
		if ( IEIter != m_Factorys.end() )
		//..�� IEFactory ��������� �� ������ Factory ���
		IEFactory = IEIter->second;
		else IEFactory = m_Factorys[UDH_IE_unknown];//�� �������� ��� ������ ����

	CH<IIE> ie = IEFactory->Make(buffer);
	SetIE (ie);
	//�� � ��������� ����� ������
	BuffLen -= ie->GetLength(); //����� IE
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
//���� Factory � ������, ���� �������...
IEsMAP::const_iterator IEsIter = m_IEs.find( IEI );
CH<IIEFactory> IEFactory;
	if ( IEsIter != m_IEs.end() ) return IEsIter->second;
	else{//����� �� �����������
	CH<IEUnknown> unKnown;
	//� ������ ����������, ������ ��������� � ��������� �� ����
	return SafeCastCH<IIE, IEUnknown>(unKnown);
	}
}

////////////////////////////////////////////////////////
void
CUDHImpl::SetIE( CH<IIE> ie ){
m_IEs[ ie->GetIEI() ] = ie;

#pragma chMSG( "CUDHImpl::SetIE:: Fix it later. ���������� �������� ����� �� ��� ���, � ����������, � �� �����������!" )
//���������� ����� �����
#pragma warning(push)
#pragma warning(disable:4244)
m_RawLength += ie->GetLength(); //����� IE
#pragma warning(pop)
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CUDHImpl::GetRawData(){
CH<IRawBuffer> retVal;

//��������� �� �������:
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