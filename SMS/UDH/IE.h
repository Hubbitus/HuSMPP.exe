////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : IE.h
// Pavel Alexeev
// Created 2007-06-27 15:30
////////////////////////////////////////////////////////

#pragma once
#include "../../HuSMPPshared.h"
#include "../../Utils/rawbuffer.h"

////////////////////////////////////////////////////////
// useful macroses to define diffeent IEs
////////////////////////////////////////////////////////
/*IEDL - IE Data Length, длина всего элемента в октетах*/
#define IE_BASICS_DECLARATION( LengthType ) \
public: \
	virtual void Initialize( CH<IRawBuffer> rawBuff ); \
	virtual int GetIEI () {return m_IEI;}; \
	virtual WORD GetIEDL (){return m_IEDL;}; \
	/* Полная длина IE */ \
	virtual WORD GetLength (){return (sizeof(BYTE) + sizeof(m_IEDL) + m_IEDL);}; \
	virtual CH<IRawBuffer> GetValue() {return m_Value;}; \
	\
	virtual CH<IRawBuffer> GetRawData(); \
	virtual void parseRealValues(); \
	virtual operator std::string (); \
private: \
	int m_IEI; \
	LengthType m_IEDL; \
	CH<IRawBuffer> m_Value;
/* m_IEI НЕОБХОДИМО со знаком, чтобы для неизвестного -1 задавать, и с ним сравнивать,
поскольку 0 корректное знаяение для склеенного сообщения (IEconcatenated).
Именно поэтому, там где дальше нужна будет его длина, используем syzeof(BYTE) вместо
более красивого и более логичного sizeof(m_IEI)!!!
*/

////////////////////////////////////////////////////////
#define IE_BASICS_DEFINITION( Type, LengthType ) \
	CH<IRawBuffer> Type::GetRawData(){ \
		CH<IRawBuffer> retVal; \
		retVal->AddData( (BYTE *)(&m_IEI), sizeof(BYTE));	/*Add IEI*/ \
		retVal->AddData( (BYTE *)(&m_IEDL), sizeof(m_IEDL));/*Add IEDL*/ \
		retVal->AddData( m_Value->PeekData(), m_IEDL ); \
	return retVal; \
	} \
	void Type::Initialize( CH<IRawBuffer> rawBuff ){ \
	rawBuff->GetBYTE();	/*IEI, Он и так прописан*/ \
	m_IEDL = rawBuff->GetBYTE(); \
		if (m_IEDL > rawBuff->GetAvailableDataSize()) m_IEDL = (LengthType)rawBuff->GetAvailableDataSize(); \
	/*Скопируем и УДАЛИМ (извлечем) из переданного буфера то что относится к данному параметру*/ \
	m_Value->Clear(); \
	m_Value->AddData(rawBuff->PeekData(), m_IEDL); \
	rawBuff->Skip(m_IEDL); \
	parseRealValues(); /*вот это у всех разное уже!!!*/ \
	}

////////////////////////////////////////////////////////
class IIE{
public:
/*+74.3 если написать "= 0", то ЛЮБОЙ класс, наследующий этот через сколько угодно уровней, должен будет сам определить метод Initialize!
И мне так и не удалось сделать реализацию этого метода единой :(
*/
	virtual void Initialize( CH<IRawBuffer> rawBuff ) = 0;

	virtual int GetIEI () = 0;
	virtual WORD GetLength () = 0;
	virtual CH<IRawBuffer> GetValue() = 0;

	virtual CH<IRawBuffer> GetRawData() = 0;
	virtual void parseRealValues() = 0;
	virtual operator std::string () = 0; 

//Большинство определений в макросе
DECLARE_CH_REFCOUNTING( IIE )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////