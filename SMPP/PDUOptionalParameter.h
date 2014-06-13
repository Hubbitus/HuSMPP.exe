////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUOptionalParameter.h
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2007-11-29
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"
#include "../Utils/rawbuffer.h"

#include "PDUConsts.h"

#include <string>
#include <sstream>

////////////////////////////////////////////////////////
// useful macroses to define diffeent OPTs
////////////////////////////////////////////////////////
#define OPT_BASICS_DECLARATION(RealType, TAG_ID) \
	public: \
		typedef RealType REALTYPE; \
		virtual WORD GetTagId(){ return m_TagId; }; \
		virtual REALTYPE GetRealValue (){ return m_realValue; }; \
		virtual operator std::string (){ \
			std::ostringstream lStringOS; \
			lStringOS << m_realValue; \
			return lStringOS.str(); } \
	protected: \
		static const WORD m_TagId = TAG_ID; \
		REALTYPE m_realValue;

////////////////////////////////////////////////////////
class IPDUOptionalParameter{
public:
	virtual void Initialize( CH<IRawBuffer> value ) = 0;
	//-47 ������������� �� ������ � BYTE, ��������, ��� ��������
	virtual void Initialize( std::string val ) = 0;
//-79	virtual void Initialize( BYTE val ) = 0;

	//��� ���������� ���� � �������
	virtual WORD GetTagId() { return PDU_OPT_UNKNOWN; };
	virtual CH<IRawBuffer> GetValue(){ return m_Value; };

	//����� � ������ VALUE, ��� ����� ���� TagID � ����� Length
	virtual WORD GetLength(){ return (WORD)m_Value->GetAvailableDataSize(); };
	//����� ����� � ����� ������, � �������� �������� ����
	virtual WORD GetNetLength(){ return htons((WORD)m_Value->GetAvailableDataSize()); };

	virtual CH<IRawBuffer> GetRawData(){
	CH<IRawBuffer> retVal;

	WORD tmp = htons (GetTagId());//Neccesary, because ->AddData want pointer
	retVal->AddData( (BYTE *) (&tmp), sizeof(WORD)); //��������� TagID
	tmp = GetNetLength();
	retVal->AddData( (BYTE *) (&tmp), sizeof(WORD));
	retVal->AddData( GetValue()->PeekData(), GetLength() );
	return retVal;	
	};

	//������ ��� � ������ ������������
	virtual operator std::string () { return "<!InVaLiD!>"; };
protected:
	CH<IRawBuffer> m_Value;

//OPT_BASICS_DECLARATION( void, PDU_OPT_UNKNOWN )
DECLARE_CH_REFCOUNTING( IPDUOptionalParameter )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////