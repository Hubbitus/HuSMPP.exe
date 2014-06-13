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
	//-47 Инициализация из строки и BYTE, наоборот, для отправки
	virtual void Initialize( std::string val ) = 0;
//-79	virtual void Initialize( BYTE val ) = 0;

	//Они определены ниже в макросе
	virtual WORD GetTagId() { return PDU_OPT_UNKNOWN; };
	virtual CH<IRawBuffer> GetValue(){ return m_Value; };

	//Длина в байтах VALUE, БЕЗ учета длин TagID и самой Length
	virtual WORD GetLength(){ return (WORD)m_Value->GetAvailableDataSize(); };
	//Длина чтобы в сокет пихать, с обратным порядком байт
	virtual WORD GetNetLength(){ return htons((WORD)m_Value->GetAvailableDataSize()); };

	virtual CH<IRawBuffer> GetRawData(){
	CH<IRawBuffer> retVal;

	WORD tmp = htons (GetTagId());//Neccesary, because ->AddData want pointer
	retVal->AddData( (BYTE *) (&tmp), sizeof(WORD)); //Добавляем TagID
	tmp = GetNetLength();
	retVal->AddData( (BYTE *) (&tmp), sizeof(WORD));
	retVal->AddData( GetValue()->PeekData(), GetLength() );
	return retVal;	
	};

	//Должны все в строки конвертиться
	virtual operator std::string () { return "<!InVaLiD!>"; };
protected:
	CH<IRawBuffer> m_Value;

//OPT_BASICS_DECLARATION( void, PDU_OPT_UNKNOWN )
DECLARE_CH_REFCOUNTING( IPDUOptionalParameter )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////