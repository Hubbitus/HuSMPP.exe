////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUConsts.h

#pragma once

////////////////////////////////////////////////////////
#define PDU_INVALID_ID 0
#define PDU_UNKNOWN_ID 0

#define PDU_OUTBIND_ID 0x0000000B
//+91+4
#define PDU_BIND_RECEIVER_ID 0x00000001
#define PDU_BIND_RECEIVER_RESP_ID 0x80000001
#define PDU_BIND_TRANSMITTER_ID 0x00000002
#define PDU_BIND_TRANSMITTER_RESP_ID 0x80000002
#define PDU_BIND_TRANSCEIVER_ID 0x00000009
#define PDU_BIND_TRANSCEIVER_RESP_ID 0x80000009

#define PDU_ENQUIRE_LINK_ID 0x00000015
#define PDU_ENQUIRE_LINK_RESP_ID 0x80000015
#define PDU_GENERIC_NACK_ID 0x80000000

#define PDU_UNBIND_ID 0x00000006
#define PDU_UNBIND_RESP_ID 0x80000006

#define PDU_SUBMIT_SM_ID 0x00000004
#define PDU_SUBMIT_SM_RESP_ID 0x80000004

#define PDU_DELIVER_SM_ID 0x00000005
#define PDU_DELIVER_SM_RESP_ID 0x80000005

#define PDU_DATA_SM_ID 0x00000103
#define PDU_DATA_SM_RESP_ID 0x80000103

////////////////////////////////////////////////////////
inline bool IsPDURespCode( DWORD code ){
return (( code & 0x80000000 ) != 0);
}

////////////////////////////////////////////////////////
#define PDU_34_VERSION 0x34
#define PDU_DEFAULT_VERSION 0x34

////////////////////////////////////////////////////////

#define ESME_ROK 0x00000000
#define ESME_RINVMSGLEN 0x00000001
#define ESME_RINVCMDLEN 0x00000002
#define ESME_RINVCMDID 0x00000003
#define ESME_RINVBNDSTS 0x00000004
#define ESME_RALYBND 0x00000005
#define ESME_RINVPRTFLG 0x00000006
#define ESME_RINVREGDLVFLG 0x00000007
#define ESME_RSYSERR 0x00000008
#define ESME_RINVSRCADR 0x0000000A
#define ESME_RINVDSTADR 0x0000000B
#define ESME_RINVMSGID 0x0000000C
#define ESME_RBINDFAIL 0x0000000D
#define ESME_RINVPASWD 0x0000000E
#define ESME_RINVSYSID 0x0000000F
#define ESME_RCANCELFAIL 0x00000011
#define ESME_RREPLACEFAIL 0x00000013
#define ESME_RMSGQFUL 0x00000014
#define ESME_RINVSERTYP 0x00000015
#define ESME_RINVNUMDESTS 0x00000033
#define ESME_RINVDLNAME 0x00000034
#define ESME_RINVDESTFLAG 0x00000040
#define ESME_RINVSUBREP 0x00000042
#define ESME_RINVESMCLASS 0x00000043
#define ESME_RCNTSUBDL 0x00000044
#define ESME_RSUBMITFAIL 0x00000045
#define ESME_RINVSRCTON 0x00000048
#define ESME_RINVSRCNPI 0x00000049
#define ESME_RINVDSTTON 0x00000050
#define ESME_RINVDSTNPI 0x00000051
#define ESME_RINVSYSTYP 0x00000053
#define ESME_RINVREPFLAG 0x00000054
#define ESME_RINVNUMMSGS 0x00000055
#define ESME_RTHROTTLED 0x00000058
#define ESME_RINVSCHED 0x00000061
#define ESME_RINVEXPIRY 0x00000062
#define ESME_RINVDFTMSGID 0x00000063
#define ESME_RX_T_APPN 0x00000064
#define ESME_RX_P_APPN 0x00000065
#define ESME_RX_R_APPN 0x00000066
#define ESME_RQUERYFAIL 0x00000067
#define ESME_RINVOPTPARSTREAM 0x000000C0
#define ESME_ROPTPARNOTALLWD 0x000000C1
#define ESME_RINVPARLEN 0x000000C2
#define ESME_RMISSINGOPTPARAM 0x000000C3
#define ESME_RINVOPTPARAMVAL 0x000000C4
#define ESME_RDELIVERYFAILURE 0x000000FE
#define ESME_RUNKNOWNERR 0x000000FF

#define ESME_FLUSHERR 0x0000FFFF	//Ошибка "не дождались хорошего"

/*-47
////////////////////////////////////////////////////////
#define SMPP_DEFS_OPT_dest_addr_subunit 0x0005
#define SMPP_DEFS_OPT_dest_network_type 0x0006
#define SMPP_DEFS_OPT_dest_bearer_type 0x0007
#define SMPP_DEFS_OPT_dest_telematics_id 0x0008
#define SMPP_DEFS_OPT_source_addr_subunit 0x000D
#define SMPP_DEFS_OPT_source_network_type 0x000E
#define SMPP_DEFS_OPT_source_bearer_type 0x000F
#define SMPP_DEFS_OPT_source_telematics_id 0x0010
#define SMPP_DEFS_OPT_qos_time_to_live 0x0017
#define SMPP_DEFS_OPT_payload_type 0x0019
#define SMPP_DEFS_OPT_additional_status_info_text 0x001D
#define SMPP_DEFS_OPT_receipted_message_id 0x001E
#define SMPP_DEFS_OPT_ms_msg_wait_facilities 0x0030
#define SMPP_DEFS_OPT_privacy_indicator 0x0201
#define SMPP_DEFS_OPT_source_subaddress 0x0202
#define SMPP_DEFS_OPT_dest_subaddress 0x0203
#define SMPP_DEFS_OPT_user_message_reference 0x0204
#define SMPP_DEFS_OPT_user_response_code 0x0205
#define SMPP_DEFS_OPT_source_port 0x020A
#define SMPP_DEFS_OPT_destination_port 0x020B
#define SMPP_DEFS_OPT_sar_msg_ref_num 0x020C
#define SMPP_DEFS_OPT_language_indicator 0x020D
#define SMPP_DEFS_OPT_sar_total_segments 0x020E
#define SMPP_DEFS_OPT_sar_segment_seqnum 0x020F
#define SMPP_DEFS_OPT_SC_interface_version 0x0210
#define SMPP_DEFS_OPT_callback_num_pres_ind 0x0302
#define SMPP_DEFS_OPT_callback_num_atag 0x0303
#define SMPP_DEFS_OPT_number_of_messages 0x0304
#define SMPP_DEFS_OPT_callback_num 0x0381
#define SMPP_DEFS_OPT_dpf_result 0x0420
#define SMPP_DEFS_OPT_set_dpf 0x0421
#define SMPP_DEFS_OPT_ms_availability_status 0x0422
#define SMPP_DEFS_OPT_network_error_code 0x0423
#define SMPP_DEFS_OPT_message_payload 0x0424
#define SMPP_DEFS_OPT_delivery_failure_reason 0x0425
#define SMPP_DEFS_OPT_more_messages_to_send 0x0426
#define SMPP_DEFS_OPT_message_state 0x0427
#define SMPP_DEFS_OPT_ussd_service_op 0x0501
#define SMPP_DEFS_OPT_display_time 0x1201
#define SMPP_DEFS_OPT_sms_signal 0x1203
#define SMPP_DEFS_OPT_ms_validity 0x1204
#define SMPP_DEFS_OPT_alert_on_message_delivery 0x130C
#define SMPP_DEFS_OPT_its_reply_type 0x1380
#define SMPP_DEFS_OPT_its_session_info 0x1383
*/
////////////////////////////////////////////////////////
#define ESM_CLASS_DEFAULT 0x0
#define ESM_CLASS_DATAGRAM_MODE 0x1
#define ESM_CLASS_TRANSACTION_MODE 0x2
#define ESM_CLASS_STOREANDFORWARD_MODE 0x3

//-41//////////////////////////////////////////////////////
//-85 #define PDU_OPT_INVALID			0x0
#define PDU_OPT_UNKNOWN				0x0
#define PDU_OPT_DeliverRoute		0x1402	// "Reserved" for Incore!
#define PDU_OPT_UserResponseCode	0x0205	// 5.3.2.18
#define PDU_OPT_MessagePayload		0x0424	// 5.3.2.32
//+79 4 more
#define PDU_OPT_NetworkErrorCode	0x0423	// 5.3.2.31 "ErrorType" by WireShark
#define PDU_OPT_MessageState		0x0427	// 5.3.2.25
#define PDU_OPT_ReceiptedMessageId	0x001E	// 5.3.2.12 "SMSC identifier" by WireShark
#define PDU_OPT_SourceSubaddress	0x0202	// 5.3.2.15
#define PDU_OPT_SCInterfaceVersion	0x0210	// 5.3.2.25 "SMSC-supported version" by WireShark
//+93 3 more
#define PDU_OPT_SarMsgRefNum		0x020C	// 5.3.2.22
#define PDU_OPT_SarTotalSegments	0x020E	// 5.3.2.23
#define PDU_OPT_SarSegmentSeqnum	0x020F	// 5.3.2.24

////////////////////////////////////////////////////////
//+74
#define UDH_IE_unknown -1				//00 - валиден
#define UDH_IE_concatenated 0x00		//Склеенные сообщений, 8-битный индекс
#define UDH_IE_concatenated_long 0x08	//Склеенные сообщений, 16-битный индекс

// =================== END OF FILE =====================
////////////////////////////////////////////////////////