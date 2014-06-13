//////////////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : InSMS.cpp
// Author  : Pavel Alexeev
// Rewritten in HuSMPP by Pavel Alexeev 2008-07-30
//	2008-07-30
//	- Replace CString to std::string in inSMSLog property and appropriate methods
//
//	2008-08-28
//	- Move Delivery - related methods into separate Delivery class
//	- Steep from CH<> template-model to using boost::shared_ptr.
//		So, we can now use normal inheritance without hacks, tricks and restrictions!
//
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InSMS.h"

#include "UDH/IEs/IEConcatenated.h"
#include "UDH/IEs/IEConcatenated_long.h"

#include "../Common/Singles/singleton.h" //для логов

//////////////////////////////////////////////////////////////////
InSMS::InSMS(CH<IPDUDeliverSm> pdu){
isParsed = false;
m_lOption = 0;

msgPartNo = msgPartsTotal = 1;
msgPartLinkID = 0;

inSMSLog = "";

//Inizialisation
ASSERT(m_pdu);
m_pdu = pdu;
ParseSMS();	
}

//////////////////////////////////////////////////////////////////
void
InSMS::ParseSMS(){
inSMSLog = "";
body = m_pdu->GetShortMessage();
//*85	if ( "" == body && GetOptionalParameter(PDU_OPT_MessagePayload)->GetTagId() != PDU_OPT_INVALID){
	if ( "" == body && GetOptionalParameter(PDU_OPT_MessagePayload)->GetTagId() != PDU_OPT_UNKNOWN){
	body = GetOptionalParameterStr(PDU_OPT_MessagePayload);
	inSMSLog = "Body EMPTY, got MsgPayload;";
	}

	if (!isDeliveryNotification()){//Normal SMS
		if (isUDH()){
		parseUDH();
		inSMSLog += "has UDH:";
		CH<IIEsIterator> IIsIter = m_UDH->GetIEs();
			while (IIsIter->More()){//В лог все что разобрали!
			CH<IIE> ie = IIsIter->Next();
			inSMSLog += " " + ie->operator std::string() + ";";
			}
		}

		if (isUCS2()){
		body = SMS::UCS2toCP1251(body);
		}
		else body = body.c_str();

		//+93 Alternative Sar_ concatanation.
		//We may check only one this because if it present, 2 other sar_* must be present by specification ver 3.4
		if ( GetOptionalParameter(PDU_OPT_SarMsgRefNum)->GetTagId() != PDU_OPT_UNKNOWN){
		msgPartLinkID	= (SafeDynamicCastCH<OPTSarMsgRefNum, IPDUOptionalParameter>(GetOptionalParameter(PDU_OPT_SarMsgRefNum)))->GetRealValue();
		msgPartsTotal	= (SafeDynamicCastCH<OPTSarTotalSegments, IPDUOptionalParameter>(GetOptionalParameter(PDU_OPT_SarTotalSegments)))->GetRealValue();
		msgPartNo		= (SafeDynamicCastCH<OPTSarSegmentSeqnum, IPDUOptionalParameter>(GetOptionalParameter(PDU_OPT_SarSegmentSeqnum)))->GetRealValue();
		}
	}

isParsed = true;
}

//////////////////////////////////////////////////////////////////
void
InSMS::parseUDH(){
	if (body.length() > 0){
	BYTE UDHL = body[0];	//Длина всего заголовка UDH
	CH<IRawBuffer> rawBuf;
	rawBuf->AddData( (const BYTE *) body.substr(1, UDHL).data(), UDHL);
	m_UDH->Initialize(rawBuf);

	body = body.substr(
		sizeof(BYTE) //UDHL
		+UDHL
	);//Оставшуюся часть

		if (m_UDH->GetIE(UDH_IE_concatenated)->GetIEI() != UDH_IE_unknown){
/*
	CH<IEConcatenated> ieConc; //ПРИХОДИТСЯ через RawBuffer инициализировать, из-за использования CH и, соответственно, невозможности сделать нечто вроде dynamic_cast
	ieConc->Initialize(m_UDH->GetIE(UDH_IE_concatenated)->GetRawData());
	msgPartLinkID	= ieConc->msgPartLinkID();
	msgPartsTotal	= ieConc->msgPartsTotal();
	msgPartNo		= ieConc->msgPartNo();
*/
//	msgPartLinkID	= m_UDH->GetIE(UDH_IE_concatenated)->msgPartLinkID();
		msgPartLinkID	= (SafeDynamicCastCH<IEConcatenated, IIE> (m_UDH->GetIE(UDH_IE_concatenated)))->msgPartLinkID();
		msgPartsTotal	= (SafeDynamicCastCH<IEConcatenated, IIE> (m_UDH->GetIE(UDH_IE_concatenated)))->msgPartsTotal();
		msgPartNo		= (SafeDynamicCastCH<IEConcatenated, IIE> (m_UDH->GetIE(UDH_IE_concatenated)))->msgPartNo();
		}else if (m_UDH->GetIE(UDH_IE_concatenated_long)->GetIEI() != UDH_IE_unknown){
		msgPartLinkID	= (SafeDynamicCastCH<IEConcatenated_long, IIE> (m_UDH->GetIE(UDH_IE_concatenated_long)))->msgPartLinkID();
		msgPartsTotal	= (SafeDynamicCastCH<IEConcatenated_long, IIE> (m_UDH->GetIE(UDH_IE_concatenated_long)))->msgPartsTotal();
		msgPartNo		= (SafeDynamicCastCH<IEConcatenated_long, IIE> (m_UDH->GetIE(UDH_IE_concatenated_long)))->msgPartNo();
		}
	}
}

//////////////////////////////////////////////////////////////////
bool
InSMS::isNoOption(){
return (
	(m_pdu->GetDataCoding() & 252 /*11111100*/) == 252
);//Если 7-2 биты нулевые
}


//////////////////////////////////////////////////////////////////
bool
InSMS::isDeliveryReceiptRequested(){
chASSERT ( isParsed );
return ( 
	((m_pdu->GetEsmClass() & 60 /*60=00111100*/) == 4) /*xx0001xx*/
);
}

//////////////////////////////////////////////////////////////////
bool	//By WireShark: ..00 01.. = Message type  : Short message contains SMSC Delivery Receipt (0x01)
InSMS::isDeliveryNotification(){
return m_pdu->isDeliveryNotification();
}

//////////////////////////////////////////////////////////////////
bool
InSMS::is8bit(){
BYTE dcs = m_pdu->GetDataCoding();
return ( 
	( (!((dcs & 192) == 192)) && ((dcs & 4) == 4) ) /*11000000, 00000100 Если старшие 2 нули, а 3й - 1*/
	||
	((dcs & 244) == 244) /*11110100*/
);
}

//////////////////////////////////////////////////////////////////
bool
InSMS::isUDH(){
return (
	(m_pdu->GetEsmClass() & 64 /*64=01000000*/) == 64
);
}

//////////////////////////////////////////////////////////////////
bool
InSMS::isUCS2(){
BYTE dcs = m_pdu->GetDataCoding();
return ( 
	( ((dcs & 192) == 0) && ((dcs & 8) == 8) ) /*11000000, 00001000 Если старшие 2 нули, а 3й - 1*/
	||
	((dcs & 224) == 224) /*11100000*/
);
}

//////////////////////////////////////////////////////////////////
bool
InSMS::isEMS(){
#pragma chMSG("Fix it later")

return false;	
}