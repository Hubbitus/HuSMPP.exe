////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IEConcatenated.cpp
// Pavel Alexeev
// Created 2007-06-27 16:44
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEConcatenated.h"
#include <sstream>
////////////////////////////////////////////////////////

class IEConcatenatedImpl : public IEConcatenated{
public:
	IEConcatenatedImpl();
	virtual ~IEConcatenatedImpl();

////////////////////IE_BASICS_DECLARATION
/*
public:
	virtual void Initialize( CH<IRawBuffer> rawBuff );
	virtual int GetIEI () {return m_IEI;};
	virtual WORD GetIEDL (){return m_IEDL;};
	// Полная длина IE
	virtual WORD GetLength (){
	WORD ttt = 0;
	ttt += sizeof(BYTE);
	ttt += sizeof(m_IEDL);
	ttt += m_IEDL;
	return ttt;
	};
	virtual CH<IRawBuffer> GetValue() {return m_Value;};

	virtual CH<IRawBuffer> GetRawData();
	virtual void parseRealValues();
	virtual operator std::string ();
private:
	int m_IEI;
	//Переопределить, если другой длины у потомка!!!
	BYTE m_IEDL;
	CH<IRawBuffer> m_Value;
////////////////////IE_BASICS_DECLARATION
*/
IE_BASICS_DECLARATION( BYTE )
};

/////////////IE_BASICS_DEFINITION( IEConcatenatedImpl )
/*
CH<IRawBuffer>
IEConcatenatedImpl::GetRawData(){
CH<IRawBuffer> retVal;

//std::string str ((char *)retVal->PeekData(), retVal->GetAvailableDataSize());
retVal->AddData( (BYTE *)(&m_IEI), sizeof(BYTE)); // Add IEI
retVal->AddData( (BYTE *)(&m_IEDL), sizeof(m_IEDL)); //Add IEDL
std::string str1 ((char *)retVal->PeekData(), retVal->GetAvailableDataSize());
retVal->AddData( (BYTE *)m_Value->PeekData(), m_IEDL );
std::string str2 ((char *)retVal->PeekData(), retVal->GetAvailableDataSize());
return retVal;
}

void IEConcatenatedImpl::Initialize( CH<IRawBuffer> rawBuff ){
int tttt = rawBuff->GetBYTE();	//IEI, Он и так прописан
m_IEDL = rawBuff->GetBYTE();
	if (m_IEDL > rawBuff->GetAvailableDataSize()) m_IEDL = (BYTE)rawBuff->GetAvailableDataSize();
//Скопируем и УДАЛИМ (извлечем) из переданного буфера то что относится к данному параметру
m_Value->Clear();
m_Value->AddData(rawBuff->PeekData(), m_IEDL);
rawBuff->Skip(m_IEDL);
parseRealValues(); //вот это у всех разное уже!!!
}
*/
/////////////IE_BASICS_DEFINITION( IEConcatenatedImpl )
IE_BASICS_DEFINITION( IEConcatenatedImpl, BYTE )

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IEConcatenated, IEConcatenatedImpl )

////////////////////////////////////////////////////////
IEConcatenatedImpl::IEConcatenatedImpl()
	: m_IEI ( UDH_IE_concatenated )
/*+74.3 В упор не понимаю почему так нельзя инициализировать наследованные protected-члены!
,m_msgPartLinkID (0), m_msgPartsTotal (1), m_msgPartNo (0)*/{
m_msgPartLinkID = 0;
m_msgPartsTotal = 1;
m_msgPartNo = 1;
}

////////////////////////////////////////////////////////
IEConcatenatedImpl::~IEConcatenatedImpl(){
}

////////////////////////////////////////////////////////
void
IEConcatenatedImpl::parseRealValues(){
CH<IRawBuffer> tmpBuff = m_Value->Clone();
m_msgPartLinkID = tmpBuff->GetBYTE();

m_msgPartsTotal = tmpBuff->GetBYTE();
m_msgPartNo = tmpBuff->GetBYTE();
}

////////////////////////////////////////////////////////
IEConcatenatedImpl::operator std::string () {
std::ostringstream lStringOS;
lStringOS << "IE Conc: " << "LinkID=" << m_msgPartLinkID << " Part: " << m_msgPartNo << '/' << m_msgPartsTotal;
return lStringOS.str();
}
// =================== END OF FILE =====================
////////////////////////////////////////////////////////