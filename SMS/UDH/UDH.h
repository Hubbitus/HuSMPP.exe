////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : UDH.h
// Pavel Alexeev
// Created 2007-06-27 14:23
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////
#include "../../Utils/rawbuffer.h"
#include "IEsIterator.h"
#include "IEFactory.h"

#include "IEs/IEUnknown.h"

#include "IEs/Factories/IEUnknownFactory.h"
#include "IEs/Factories/IEConcatenatedFactory.h"
#include "IEs/Factories/IEConcatenated_longFactory.h"

#include <map>
////////////////////////////////////////////////////////

class IUDH{
public:
	virtual void Initialize( CH<IRawBuffer> buffer ) = 0;
	virtual CH<IIEsIterator> GetIEs() = 0;
	virtual CH<IIE> GetIE( WORD IEI ) = 0;
	virtual void SetIE( CH<IIE> IEI ) = 0;

	virtual CH<IRawBuffer> GetRawData() = 0;
	//Длина в байтах (Октетах) всех IEs (для сокета?)
	virtual WORD GetRawLength () = 0;
protected:
	typedef map< int, CH<IIE> > IEsMAP;
	IEsMAP m_IEs;

	//Фабрики
	typedef map<int, CH<IIEFactory> > IEsFactoryMAP;
	IEsFactoryMAP m_Factorys;

	//Длина, для помещения в сокет, если потребуется
	WORD m_RawLength;

public:
  DECLARE_CH_REFCOUNTING( IUDH )
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////