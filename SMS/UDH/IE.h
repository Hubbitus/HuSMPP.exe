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
/*IEDL - IE Data Length, ����� ����� �������� � �������*/
#define IE_BASICS_DECLARATION( LengthType ) \
public: \
	virtual void Initialize( CH<IRawBuffer> rawBuff ); \
	virtual int GetIEI () {return m_IEI;}; \
	virtual WORD GetIEDL (){return m_IEDL;}; \
	/* ������ ����� IE */ \
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
/* m_IEI ���������� �� ������, ����� ��� ������������ -1 ��������, � � ��� ����������,
��������� 0 ���������� �������� ��� ���������� ��������� (IEconcatenated).
������ �������, ��� ��� ������ ����� ����� ��� �����, ���������� syzeof(BYTE) ������
����� ��������� � ����� ��������� sizeof(m_IEI)!!!
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
	rawBuff->GetBYTE();	/*IEI, �� � ��� ��������*/ \
	m_IEDL = rawBuff->GetBYTE(); \
		if (m_IEDL > rawBuff->GetAvailableDataSize()) m_IEDL = (LengthType)rawBuff->GetAvailableDataSize(); \
	/*��������� � ������ (��������) �� ����������� ������ �� ��� ��������� � ������� ���������*/ \
	m_Value->Clear(); \
	m_Value->AddData(rawBuff->PeekData(), m_IEDL); \
	rawBuff->Skip(m_IEDL); \
	parseRealValues(); /*��� ��� � ���� ������ ���!!!*/ \
	}

////////////////////////////////////////////////////////
class IIE{
public:
/*+74.3 ���� �������� "= 0", �� ����� �����, ����������� ���� ����� ������� ������ �������, ������ ����� ��� ���������� ����� Initialize!
� ��� ��� � �� ������� ������� ���������� ����� ������ ������ :(
*/
	virtual void Initialize( CH<IRawBuffer> rawBuff ) = 0;

	virtual int GetIEI () = 0;
	virtual WORD GetLength () = 0;
	virtual CH<IRawBuffer> GetValue() = 0;

	virtual CH<IRawBuffer> GetRawData() = 0;
	virtual void parseRealValues() = 0;
	virtual operator std::string () = 0; 

//����������� ����������� � �������
DECLARE_CH_REFCOUNTING( IIE )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////