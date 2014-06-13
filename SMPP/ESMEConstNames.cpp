////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : ESMEConstNames.h
// Author  : Pavel Alexeev (Pahan-Hubbitus)
// Date	   : 2008-07-21
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ESMEConstNames.h"
#include "SMPP/PDUConsts.h"

////////////////////////////////////////////////////////

ESMEConstNames::ESMEConstNames(void){
/* Descriptions from SMPP 3.4 standart.
Table 5-2: SMPP Error Codes

Formatted by replace with regularExpressions:
{:b0x000000[0-9A-F]+:b}{.+}
to
] /*\1 * / = "\2";
(on string before "* /" mangled by add space, to not break comment)
*/

names_[ESME_ROK] /* 0x00000000 */ = "No Error";
names_[ESME_RINVMSGLEN] /* 0x00000001 */ = "Message Length is invalid";
names_[ESME_RINVCMDLEN] /* 0x00000002 */ = "Command Length is invalid";
names_[ESME_RINVCMDID] /* 0x00000003 */ = "Invalid Command ID";
names_[ESME_RINVBNDSTS] /* 0x00000004 */ = "Incorrect BIND Status for given command";
names_[ESME_RALYBND] /* 0x00000005 */ = "ESME Already in Bound State";
names_[ESME_RINVPRTFLG] /* 0x00000006 */ = "Invalid Priority Flag";
names_[ESME_RINVREGDLVFLG] /* 0x00000007 */ = "Invalid Registered Delivery Flag";
names_[ESME_RSYSERR] /* 0x00000008 */ = "System Error";
//Reserved 0x00000009
names_[ESME_RINVSRCADR] /* 0x0000000A */ = "Invalid Source Address";
names_[ESME_RINVDSTADR] /* 0x0000000B */ = "Invalid Dest Addr";
names_[ESME_RINVMSGID] /* 0x0000000C */ = "Message ID is invalid";
names_[ESME_RBINDFAIL] /* 0x0000000D */ = "Bind Failed";
names_[ESME_RINVPASWD] /* 0x0000000E */ = "Invalid Password";
names_[ESME_RINVSYSID] /* 0x0000000F */ = "Invalid System ID";
//Reserved 0x00000010
names_[ESME_RCANCELFAIL] /* 0x00000011 */ = "Cancel SM Failed";
//Reserved 0x00000012
names_[ESME_RREPLACEFAIL] /* 0x00000013 */ = "Replace SM Failed";
names_[ESME_RMSGQFUL] /* 0x00000014 */ = "Message Queue Full";
names_[ESME_RINVSERTYP] /* 0x00000015 */ = "Invalid Service Type";
//Reserved 0x00000016-0x00000032
names_[ESME_RINVNUMDESTS] /* 0x00000033 */ = "Invalid number of destinations";
names_[ESME_RINVDLNAME] /* 0x00000034 */ = "Invalid Distribution List name";
//Reserved 0x00000035-0x0000003F
names_[ESME_RINVDESTFLAG] /* 0x00000040 */ = "Destination flag is invalid (submit_multi)";
//Reserved 0x00000041
names_[ESME_RINVSUBREP] /* 0x00000042 */ = "Invalid 'submit with replace' request (i.e. submit_sm with replace_if_present_flag set)";
names_[ESME_RINVESMCLASS] /* 0x00000043 */ = "Invalid esm_class field data";
names_[ESME_RCNTSUBDL] /* 0x00000044 */ = "Cannot Submit to Distribution List";
names_[ESME_RSUBMITFAIL] /* 0x00000045 */ = "submit_sm or submit_multi failed";
//Reserved 0x00000046-0x00000047
names_[ESME_RINVSRCTON] /* 0x00000048 */ = "Invalid Source address TON";
names_[ESME_RINVSRCNPI] /* 0x00000049 */ = "Invalid Source address NPI";
names_[ESME_RINVDSTTON] /* 0x00000050 */ = "Invalid Destination address TON";
names_[ESME_RINVDSTNPI] /* 0x00000051 */ = "Invalid Destination address NPI";
//Reserved 0x00000052
names_[ESME_RINVSYSTYP] /* 0x00000053 */ = "Invalid system_type field";
names_[ESME_RINVREPFLAG] /* 0x00000054 */ = "Invalid replace_if_present flag";
names_[ESME_RINVNUMMSGS] /* 0x00000055 */ = "Invalid number of messages";
//Reserved 0x00000056-0x00000057
names_[ESME_RTHROTTLED] /* 0x00000058 */ = "Throttling error (ESME has exceeded allowed message limits)";
//Reserved 0x00000059-0x00000060
names_[ESME_RINVSCHED] /* 0x00000061 */ = "Invalid Scheduled Delivery Time";
names_[ESME_RINVEXPIRY] /* 0x00000062 */ = "Invalid message validity period (Expiry time)";
names_[ESME_RINVDFTMSGID] /* 0x00000063 */ = "Predefined Message Invalid or Not Found";
names_[ESME_RX_T_APPN] /* 0x00000064 */ = "ESME Receiver Temporary App Error Code";
names_[ESME_RX_P_APPN] /* 0x00000065 */ = "ESME Receiver Permanent App Error Code";
names_[ESME_RX_R_APPN] /* 0x00000066 */ = "ESME Receiver Reject Message Error Code";
names_[ESME_RQUERYFAIL] /* 0x00000067 */ = "query_sm request failed";
//Reserved 0x00000068-0x000000BF
names_[ESME_RINVOPTPARSTREAM] /* 0x000000C0 */ = "Error in the optional part of the PDU Body.";
names_[ESME_ROPTPARNOTALLWD] /* 0x000000C1 */ = "Optional Parameter not allowed";
names_[ESME_RINVPARLEN] /* 0x000000C2 */ = "Invalid Parameter Length.";
names_[ESME_RMISSINGOPTPARAM] /* 0x000000C3 */ = "Expected Optional Parameter missing";
names_[ESME_RINVOPTPARAMVAL] /* 0x000000C4 */ = "Invalid Optional Parameter Value";
//Reserved 0x000000C5-0x000000FD
names_[ESME_RDELIVERYFAILURE] /* 0x000000FE */ = "Delivery Failure (used for data_sm_resp)";
names_[ESME_RUNKNOWNERR] /* 0x000000FF */ = "Unknown Error";
//Reserved for SMPP extension 0x00000100-0x000003FF
//Reserved for SMSC vendor specific errors 0x00000400-0x000004FF
//Reserved 0x00000500-0xFFFFFFFF

//This is My extension:
names_[ESME_FLUSHERR] /* 0x0000FFFF	*/ = "Flush all to error";
}

ESMEConstNames::~ESMEConstNames(void){
}
