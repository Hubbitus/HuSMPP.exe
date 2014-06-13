////////////////////////////////////////////////////////
// Project : HuSMPP
// Module  : HuSMPPshared.h
// Author  : Pavel Alexeev (Pahan-Hubbitus)
//		2008-07-24
//	- Add define WM_SMPP_BINDED.
//	- Several messages renamed from WM_* to WM_SMPP_* for more conform to idea
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#define DEBUG_SOCKET 1
#define LOG_PDU_EVENTS 1

#define MAX_ERROR_SMS_SEND 2
#define WM_SMPP_SOCKET_CONNECTED WM_USER+114
#define WM_SMPP_SOCKET_CLOSED WM_USER+115
#define WM_SMPP_BINDED WM_USER+121
//-60
#define WM_WRITE_WINDOW_LOG WM_USER+116
#define WM_SMPP_MESSAGE_RECIVED WM_USER+117
//#define WM_SUBMIT_RESP_RECIVED WM_USER+18
#define WM_SMPP_SUBMIT_RESP_SENDED WM_USER+119	//���������� ��
#define WM_SMPP_SUBMIT_RESP_FAILED WM_USER+120	//���������� ������

#define ENDLINE "\r\n"
//#define ENDLINE "\n"

#define DB_RECONNECT_TIME_SECONDS 5
////////////////////////////////////////////////////////
const char czConnectString[] = "Driver={SQL Server};Server=192.168.55.2;Database=sms;Uid=test;Pwd=123;";
////////////////////////////////////////////////////////
#include "Common/CmnHdr.h"

#include "Utils/ptrs.h"
#include "Utils/errors.h"

#include "SMPP/PDUConsts.h"	//��� ����������� �������� PDU

////////////////////////////////////////////////////////
class SMS;
class IOutSMS;

class ISMPPClient;

class Log;

class IPDU;

class IPDUCache;

class IOctString;

class IPDUBindTransceiver;
class IPDUBindTransceiverResp;
//+91+4
class IPDUBindReceiver;
class IPDUBindReceiverResp;
class IPDUBindTransmitter;
class IPDUBindTransmitterResp;
class IPDUEnquireLink;
class IPDUEnquireLinkResp;
class IPDUGenericNack;
class IPDUOutbind;
class IPDUUnknown;

class IPDUUnbind;
class IPDUUnbindResp;
class IPDUSubmitSm;
class IPDUSubmitSmResp;
class IPDUDeliverSm;
class IPDUDeliverSmResp;
class IPDUDataSm;
class IPDUDataSmResp;

class IPDUParser;

class PDUEventHandler;

class ISMPPSessionState;

class ISMPPSessionOpenState;
class ISMPPSessionClosedState;
class ISMPPSessionBoundTxState;
class ISMPPSessionBoundRxState;
class ISMPPSessionBoundTrxState;
////////////////////////////////////////////////////////
class IAction;
class INullAction;
//-52
class IUnbindAction;

class ICompositeAction;
class IConnectClientAction;
class IBindTransceiverAction;
////////////////////////////////////////////////////////
class IPDUIterator;

class IPDUFactory;
class IPDUBindTransceiverFactory;
class IPDUBindTransceiverRespFactory;
class IPDUEnquireLinkFactory;
class IPDUEnquireLinkRespFactory;
class IPDUGenericNackFactory;
class IPDUOutbindFactory;
class IPDUUnknownFactory;

class IPDUUnbindFactory;
class IPDUUnbindRespFactory;
class IPDUSubmitSmFactory;
class IPDUSubmitSmRespFactory;
class IPDUDeliverSmFactory;
class IPDUDeliverSmRespFactory;
class IPDUDataSmFactory;
class IPDUDataSmRespFactory;

////////////////////////////////////////////////////////
//-44
class IPDUOptionalParameter;
class IPDUOptionalParameters;

class IOptFactory;

class IOptUnknownFactory;
class IOptUserResponseCodeFactory;
class IOptDeliverRouteFactory;

class OPTUnknown;
class OPTUserResponseCode;
class OPTDeliverRoute;
class OPTMessagePayload;
//-44
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//+74
class IIE;
class IUDH;

class IEFactory;

class IIEUnknownFactory;
class IIEConcatenatedFactory;
class IIEConcatenated_longFactory;

class IEUnknown;
class IEConcatenated;
class IEConcatenated_long;
////////////////////////////////////////////////////////
//#define LOGFILENAME "SMSC%d.log"
#define LOGFILENAME "C:\\SMPP\\NEW_Free_lib\\LOGs\\SMSC%d.log"

////////////////////////////////////////////////////////
//?????????#include "Common/Singles/singleton.h"

//-11#define GETCONFIG CSingleton::GetInstance()->GetConfig()
#define GETLOG CSingleton::GetInstance()->GetLog()
#define GETSMSCACHE CSingleton::GetInstance()->GetSMSCache()
#define GETRESPCACHE CSingleton::GetInstance()->GetRespCache()
//-11#define GETGLOBALFUNCTIONS CSingleton::GetInstance()->GetGlobalFunctions()
//+92
#define ESMEdescription( esmeCode ) CSingleton::GetInstance()->GetESMEConstNames()->operator[](esmeCode)

const enum SocketType { Receiver = 1, Transmitter = 2, Transceiver = 4 };

// =================== END OF FILE =====================
////////////////////////////////////////////////////////

/*
����������� ������������!
�� ��� ����������� ���� //-44 ��� /*-44 */

/*
������ �������� ��������� ������ ����� ������ "#pragma once" � �����, ��� ������������ ����.
��� �������������� ������������ ����� ������������, ��� ������� ��������������� � GCC
http://en.wikipedia.org/wiki/Pragma_once


��� �� ������ � ������ ����� ������������ ������������ (/\*)|(//)-*44
(/\*)|(//)[\-\+\*]*74\.[23]

43 - �������� Mutex

44 - ���������� ������� � �������� OptionalParameters
45 - ���������, ��� ������������ ����������� � ���� 44
46 - ���������� � rawBufer ������ GetString
47 - ���������� �������� OptionalParameters
48 - ���������� resp'��. �� ������ ����, ������ action'�!!!

49 - ������� ��������� PDU (�������) �� ������->write � HuSMPPClient->Request � RequestResp, ����� ������ ���������� - 2 ���� ����-������� �������� ���

50 (17) - ���������� ���� � ����

51 - ���������! ������� �� ���������� �����
51.2 - �������

52 - ���������� �� ������ ������������ � ��������

53 - ������������� ����������, ��� ��������� (Bind �������) resp'��!

54 - �������� � ��������� ��������� ������!!
��� � �� ����� ������, �� ������-�� IOCP.PostStatus �� Socket->Close �� ����� ���������� ���������
������ ���������� ���������, �� ��������� �� ����������! �������� �������� � Socket �������� �����
getIOCP, � �������� ������� ��������� �� ��������� ������ ������������ ����� �� HuSMPPClient::SocketDisconnect!!!

55 - ��������� Singleton ��� ��������� �� ����������, � �����������, ��� ����, �� Library

56 - ��������� ����, �� ������ �� ���� ���� ���������� ( CWnd * ) � ���������� ���� HWND,
�����, ��-�� ��������������� (����������� �����) �� �������� ������� � ���� � ����, �� ������ �������!
��. wincore.cpp ������ 896-908!!!

57 - ���������� ���������

58 - ���������� ���������������������� ������!

59 - ������� �������� � �����������!

60 - ���������� ���� �� ������ ������ � ����!

61 - �����, ��������, ����� ��� �� ���������! ����� ���������� SMSCache � RespCache

62 - � ������ ���� � �� ������, � action �� ���� �������� resp!!!

63 - ���������� �������� ���, �������� (InSMS) � ��������� (IOutSMS)

64 - ������������� �������� �����
64.1 - ������������ ��������� msgID, �������� ��� �� ������� ������
64.2 - ���� ������������ ������ �������, ��� ��� �����-�� ������� �� ������

65 - ����������� �������������� ����������� ������� � ������� ������� ���. ���� �������������� ��� � �� ��� ��� ��������������, �������� ����� � ������ ������ ������

66 - ���������� OutSMS (IOutSMS) ��� ������������� � �������� CH ��� ��������������� ������������ �������� � ����� �������� �� ������

67 - ���������� InSMS (IInSMS) ��� ������������� � �������� CH ��� ��������������� ������������ �������� � ����� �������� �� ������

68 - ������� �������� �������� ����� � ���������� PDU!!!!

69 - ������ "������� ���", ������ ������ �������� ���

70 - �������� � ��������� �������� ��� ��������� ������ �������� ���

71 - ���������� �������� ������� ���������

72 - ���������� ������������ �� "��������" � "���������" PDU-������. � ������ ������� ��� ������� � ������ enquire_link (01.02.2007)

73 - ����������� ������ ������������ ������, ��� �������� ������������ ����������

74 - ���������� UDH, IEs (Information Elements ).
	�� IEs ���������� IEUnknown, UDH_IE_concatenated, UDH_IE_concatenated_long
+74.3 ���� �������� "= 0", �� ����� �����, ����������� ���� ����� ������� ������ �������, ������ ����� ��� ���������� ����� Initialize!
� ��� ��� � �� ������� ������� ���������� ����� ������ ������ :(

+75 ���������� OPTMessagePayload (��� ���-������ � ������ �������)

+76 ������ ENDLINE ������� �� std::endl

+77 ���������� �� ������ ������������ � ��������� (������ ����� �����������, MFC)!

+78 ���������� ������������� ���������� SafeDynamicCastCH!!!

+79 <2007-09-24> ���������� ��������� CheckDelivery (DeliveryReport)
79.1 - �������� ����� 	m_nAddrTON; m_nAddrNPI; �� �������:
	BYTE send_DestTON;
	BYTE send_DestNPI;
	BYTE send_SrcTON;
	BYTE send_SrcNPI;

//79.2 - �� ����������� ������, ��������

+80 - SendSMSDlg - �����������, �����������.

+81 - ENABLE most warnings (CmnHdr.h)

+82 - ������������� OptParams :) ���������������, ���������. 2007-11-29

+83 - ������������ CRawBufferImpl::GetString( WORD Size )

84 - ��������
	#define new DEBUG_NEW
	�
	static char THIS_FILE[] = __FILE__;
85 - �������� ������������� PDU_OPT_INVALID, ������ ����� ����� ���������� #define PDU_OPT_UNKNOWN			0x0,
	��� ��� ����� ���� ���������� � ���������� �������� (0x0), � ���������� ������ Unknown
	���� ���� ����� � ����������, ��������� �������.
86 - ���������� � ������������ ��������� ������:
	virtual void Initialize( REALTYPE val );
87 - �������� � ������������ �������� (���������������� ��-�� �� � �� ��������� �������������)

88 - Replace CAsyncSocket by boost.asio

89 - ������ ��� �������� �������� ������ �� boost::io_service

90 - WaitingBound*States is a extension???
	It is not described in SMPP 3.4 specifiction. See chapter 2.3 (page 17)
	But OpenState s not realized! Realize it.

91 - ���������� ������������� ����������� ������ Reciever/Transmitter
91.1 ���������� Process IPDUCache � SMPPSessionState, ������ ��� ������ ��� ������
	���������� ��������, �.�. �������� �� � ������� PDU_BASICS_DECLARATION � PDU_BASICS_DEFINITION

92 - ���������� ������ �������� ��� ��������� ����� ������ � �����:
	�������� �����: ESMEConstNames
	� ����� � �������� �������� ��������������� ����� 

93 - Realization additional OPT parameters: sar_msg_ref_num, sar_total_segments, sar_segment_seqnum
94 - 2008-09-19 Add #define WM_SMPP_SOCKET_CONNECTED WM_USER+114

95 - 2008-10-01 Add in HuSMPPClient socket connect/disconnect sincronisation.

96 - 2008-10-13 ���������� ��������������� ��������� �����.
*/