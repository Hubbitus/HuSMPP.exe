#pragma once

#include "../HuSMPPshared.h"

class IPDU;

class IPDUBindTransceiver;
class IPDUUnknown;
class IPDUBindTransceiver;
class IPDUBindTransceiverResp;
class IPDUEnquireLink;
class IPDUEnquireLinkResp;
class IPDUGenericNack;
class IPDUOutbind;

class IPDUUnbind;
class IPDUUnbindResp;
class IPDUSubmitSm;
class IPDUSubmitSmResp;
class IPDUDeliverSm;
class IPDUDeliverSmResp;
class IPDUDataSm;
class IPDUDataSmResp;

class PDUEventHandler{
private:

public:
	PDUEventHandler();
	~PDUEventHandler();

//Общий
//	virtual void OnPDUEventHandler (SP<IPDU> pdu) {defaultPDUEventHandler (pdu);};

	/*-72 "Входящие" - суффикс In это нам (чтение из сокета), на клиента, Out - уходящие (запись в сокет)*/
	/*-82
	virtual void defaultPDUEventHandlerIn (SP<IPDU> pdu){};
	virtual void defaultPDUEventHandlerOut (SP<IPDU> pdu){};
	*/
	virtual void defaultPDUEventHandlerIn (SP<IPDU> pdu)=0;
	virtual void defaultPDUEventHandlerOut (SP<IPDU> pdu)=0;

	//+91+4
	virtual void OnPDUEventHandlerIn (SP<IPDUBindReceiver> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindReceiver*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUBindReceiverResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindReceiverResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUBindTransmitter> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransmitter*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUBindTransmitterResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransmitterResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUBindTransceiver> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransceiver*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUBindTransceiverResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransceiverResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUEnquireLink> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUEnquireLink*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUEnquireLinkResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUEnquireLinkResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUGenericNack> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUGenericNack*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUOutbind> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUOutbind*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUUnknown> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUUnknown*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUUnbind> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUUnbind*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUUnbindResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUUnbindResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUSubmitSm> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUSubmitSm*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUSubmitSmResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUSubmitSmResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUDeliverSm> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUDeliverSm*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUDeliverSmResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUDeliverSmResp*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUDataSm> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUDataSm*)pdu));};
	virtual void OnPDUEventHandlerIn (SP<IPDUDataSmResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUDataSmResp*)pdu));};

	//+91+4
	virtual void OnPDUEventHandlerOut (SP<IPDUBindReceiver> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindReceiver*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUBindReceiverResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindReceiverResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUBindTransmitter> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransmitter*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUBindTransmitterResp> pdu) {defaultPDUEventHandlerIn ((IPDU*)((IPDUBindTransmitterResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUBindTransceiver> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUBindTransceiver*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUBindTransceiverResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUBindTransceiverResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUEnquireLink> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUEnquireLink*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUEnquireLinkResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUEnquireLinkResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUGenericNack> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUGenericNack*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUOutbind> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUOutbind*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUUnknown> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUUnknown*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUUnbind> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUUnbind*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUUnbindResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUUnbindResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUSubmitSm> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUSubmitSm*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUSubmitSmResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUSubmitSmResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUDeliverSm> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUDeliverSm*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUDeliverSmResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUDeliverSmResp*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUDataSm> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUDataSm*)pdu));};
	virtual void OnPDUEventHandlerOut (SP<IPDUDataSmResp> pdu) {defaultPDUEventHandlerOut ((IPDU*)((IPDUDataSmResp*)pdu));};	
};


//typedef void (PDUEventHandler::* P_PDU_EventHandler_method) ( SP<IPDU> ); //Указатель на функцию-член


struct FullPDUEventHandler{
	PDUEventHandler*			PDUEventHandlerClass; //Ссылка на объект обработчик
//	P_PDU_EventHandler_method	PDUEventHandlerMethod; //Ссылка на метод, внутри класса уже

	bool PDUHandlerOverwrite;	//ВМЕСТО ли основного или дополнительно

	//Конструктор
	FullPDUEventHandler (PDUEventHandler* PDUHandObj, /* P_PDU_EventHandler_method PDUHandMetd,*/ bool Overwrite = false){
	PDUEventHandlerClass = PDUHandObj;
//	PDUEventHandlerMethod = PDUHandMetd;
	PDUHandlerOverwrite = Overwrite;
	}
};