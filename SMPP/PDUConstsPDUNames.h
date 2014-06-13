////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : ESMEConstNames.h
// Author  : Pavel Alexeev (Pahan-Hubbitus)
// Changed : 2008-07-21
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#ifdef LOG_PDU_EVENTS
#include "stdafx.h"
#include <map>
#include <string>
#include "PDUConsts.h"

//+My ��� ���������� ���� � �����:
//���������
std::map<DWORD, std::string> PDU_DEF_NAMES;

void init_PDU_DEF_NAMES(){
PDU_DEF_NAMES[PDU_INVALID_ID] = "PDU_INVALID";
PDU_DEF_NAMES[PDU_UNKNOWN_ID] = "PDU_UNKNOWN";

PDU_DEF_NAMES[PDU_OUTBIND_ID] = "PDU_OUTBIND";
//+91+4
PDU_DEF_NAMES[PDU_BIND_RECEIVER_ID] = "PDU_BIND_RECEIVER";
PDU_DEF_NAMES[PDU_BIND_RECEIVER_RESP_ID] = "PDU_BIND_RECEIVER_RESP";
PDU_DEF_NAMES[PDU_BIND_TRANSMITTER_ID] = "PDU_BIND_TRANSMITTER";
PDU_DEF_NAMES[PDU_BIND_TRANSMITTER_RESP_ID] = "PDU_BIND_TRANSMITTER_RESP";
PDU_DEF_NAMES[PDU_BIND_TRANSCEIVER_ID] = "PDU_BIND_TRANSCEIVER";
PDU_DEF_NAMES[PDU_BIND_TRANSCEIVER_RESP_ID] = "PDU_BIND_TRANSCEIVER_RESP";

PDU_DEF_NAMES[PDU_ENQUIRE_LINK_ID] = "PDU_ENQUIRE_LINK";
PDU_DEF_NAMES[PDU_ENQUIRE_LINK_RESP_ID] = "PDU_ENQUIRE_LINK_RESP";
PDU_DEF_NAMES[PDU_GENERIC_NACK_ID] = "PDU_GENERIC_NACK";

PDU_DEF_NAMES[PDU_UNBIND_ID] = "PDU_UNBIND";
PDU_DEF_NAMES[PDU_UNBIND_RESP_ID] = "PDU_UNBIND_RESP";

PDU_DEF_NAMES[PDU_SUBMIT_SM_ID] = "PDU_SUBMIT_SM";
PDU_DEF_NAMES[PDU_SUBMIT_SM_RESP_ID] = "PDU_SUBMIT_SM_RESP";

PDU_DEF_NAMES[PDU_DELIVER_SM_ID] = "PDU_DELIVER_SM";
PDU_DEF_NAMES[PDU_DELIVER_SM_RESP_ID] = "PDU_DELIVER_SM_RESP";

PDU_DEF_NAMES[PDU_DATA_SM_ID] = "PDU_DATA_SM";
PDU_DEF_NAMES[PDU_DATA_SM_RESP_ID] = "PDU_DATA_SM_RESP";
}
#endif