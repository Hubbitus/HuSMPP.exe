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
#define WM_SMPP_SUBMIT_RESP_SENDED WM_USER+119	//Обработчик ОК
#define WM_SMPP_SUBMIT_RESP_FAILED WM_USER+120	//Обработчик Ошибки

#define ENDLINE "\r\n"
//#define ENDLINE "\n"

#define DB_RECONNECT_TIME_SECONDS 5
////////////////////////////////////////////////////////
const char czConnectString[] = "Driver={SQL Server};Server=192.168.55.2;Database=sms;Uid=test;Pwd=123;";
////////////////////////////////////////////////////////
#include "Common/CmnHdr.h"

#include "Utils/ptrs.h"
#include "Utils/errors.h"

#include "SMPP/PDUConsts.h"	//Там определение констант PDU

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
Комменатрии комменатриев!
То что указывается типа //-44 или /*-44 */

/*
Вместо сторожей включения ставлю везде только "#pragma once" в новом, или переписанном коде.
Это поддерживается большинством новых компиляторов, как минимум Мелкосовтовским и GCC
http://en.wikipedia.org/wiki/Pragma_once


Для их поиска в тексте можно использовать РегВыражение (/\*)|(//)-*44
(/\*)|(//)[\-\+\*]*74\.[23]

43 - Удаление Mutex

44 - Добавление АНАЛИЗА и парсинга OptionalParameters
45 - Временное, для последующего исправления в ходе 44
46 - Добавление в rawBufer метода GetString
47 - Добавление ОТПРАВКИ OptionalParameters
48 - Реализация resp'ов. Не всегда надо, смотри action'ы!!!

49 - Перенос обработки PDU (логгинг) из сокета->write в HuSMPPClient->Request и RequestResp, иначе ерунда получается - 2 раза туда-обратно парсится все

50 (17) - Реализация ЛОГа в файл

51 - Возможный! переход на синхронный сокет
51.2 - Обратно

52 - Избавление от ЛИШНИХ зависимостей и инклюдов

53 - Использование блокировок, для некоторых (Bind сначала) resp'ов!

54 - разборки с проблемой зависания сокета!!
Так и НЕ ПОНЯЛ почему, но почему-то IOCP.PostStatus из Socket->Close НЕ хочет вызываться нормально
точнее вызывается нормально, но результат не получается! Пришлось добавить в Socket открытый метод
getIOCP, и вызывать посылку сообщения об окончании работы паралельного треда из HuSMPPClient::SocketDisconnect!!!

55 - Изменение Singleton для инициации по требованию, а уничтожение, как было, из Library

56 - Переделка ЛОГА, не ссылку на окно надо передавать ( CWnd * ) а дескриптор окна HWND,
иначе, из-за многопоточности (асинхронный сокет) не получить доступа к логу в окне, из других потоков!
См. wincore.cpp строки 896-908!!!

57 - Реализация сообщений

58 - Добавление НЕинициализированности сокета!

59 - Решение проблемы с РЕконнектом!

60 - Реализация лога из других тредов в окно!

61 - Прием, отправка, респы все на сообщения! Также реализация SMSCache и RespCache

62 - Я клиент пишу а не сервер, в action НЕ надо отвечать resp!!!

63 - Реализация парсинга СМС, входящей (InSMS) и Исходящей (IOutSMS)

64 - Переписывание отправки СМСок
64.1 - Записывается ПОСЛЕДНИЙ msgID, наверное это не слишком хорошо
64.2 - Надо организовать повтор посылки, или еще какую-то реакцию на ошибки

65 - реализовать автоматическое кодирование русских и длинных русских СМС. Пока предполагается что в БД они уже закодированные, бинарные лежат с нужным флагом просто

66 - Реализация OutSMS (IOutSMS) для использования с шаблоном CH для автоматического освобождения ресурсов и везде передачи по ссылке

67 - Реализация InSMS (IInSMS) для использования с шаблоном CH для автоматического освобождения ресурсов и везде передачи по ссылке

68 - РЕШЕНИЕ проблемы РУССКОГО ЯЗЫКА в РЕАЛИЗАЦИИ PDU!!!!

69 - Разбор "длинных СМС", тоесть частей склееной СМС

70 - Разборки с проблемой паденрия при обработке ошибки доставки СМС

71 - Реализация отправки Русских сообщений

72 - Реализация реагирования на "Входящие" и "Исходящие" PDU-пакеты. В первую очередь для посылки и ответы enquire_link (01.02.2007)

73 - Исправление ошибки переполнения буфера, при парсинге Опциональных параметров

74 - Добавление UDH, IEs (Information Elements ).
	Из IEs реализация IEUnknown, UDH_IE_concatenated, UDH_IE_concatenated_long
+74.3 если написать "= 0", то ЛЮБОЙ класс, наследующий этот через сколько угодно уровней, должен будет сам определить метод Initialize!
И мне так и не удалось сделать реализацию этого метода единой :(

+75 Добавление OPTMessagePayload (для МТС-Сибирь в первую очередь)

+76 замена ENDLINE макроса на std::endl

+77 избавление от лишних зависимостей и включений (прежде всего стандартных, MFC)!

+78 Добавление Динамического приведения SafeDynamicCastCH!!!

+79 <2007-09-24> Добавление обработки CheckDelivery (DeliveryReport)
79.1 - убирание общих 	m_nAddrTON; m_nAddrNPI; на частные:
	BYTE send_DestTON;
	BYTE send_DestNPI;
	BYTE send_SrcTON;
	BYTE send_SrcNPI;

//79.2 - не запускается вообще, разборки

+80 - SendSMSDlg - переписываю, переделываю.

+81 - ENABLE most warnings (CmnHdr.h)

+82 - Переписывание OptParams :) Универсализация, упрощение. 2007-11-29

+83 - РеРеализация CRawBufferImpl::GetString( WORD Size )

84 - Удаление
	#define new DEBUG_NEW
	и
	static char THIS_FILE[] = __FILE__;
85 - Удаление использования PDU_OPT_INVALID, вместо этого везде используем #define PDU_OPT_UNKNOWN			0x0,
	они все равно были определены в одинаковое значение (0x0), и реализован только Unknown
	Если надо будет в дальнейшем, реализуем разницу.
86 - Добавление в опциональные параметры метода:
	virtual void Initialize( REALTYPE val );
87 - Разборки с подвисаниями апликухи (предположительно из-за БД и ее временной недоступности)

88 - Replace CAsyncSocket by boost.asio

89 - Замена где возможно Виндовых мессаг на boost::io_service

90 - WaitingBound*States is a extension???
	It is not described in SMPP 3.4 specifiction. See chapter 2.3 (page 17)
	But OpenState s not realized! Realize it.

91 - Добавление опционального раздельного режима Reciever/Transmitter
91.1 Добавление Process IPDUCache в SMPPSessionState, потому что теперь его нельзя
	определить отдельно, т.к. поместил их в макросы PDU_BASICS_DECLARATION и PDU_BASICS_DEFINITION

92 - Добавление вывода описаний для известных кодов ошибок в логах:
	Добавлен класс: ESMEConstNames
	А также в Синглтон добавлен соответствующий метод 

93 - Realization additional OPT parameters: sar_msg_ref_num, sar_total_segments, sar_segment_seqnum
94 - 2008-09-19 Add #define WM_SMPP_SOCKET_CONNECTED WM_USER+114

95 - 2008-10-01 Add in HuSMPPClient socket connect/disconnect sincronisation.

96 - 2008-10-13 Реализация автоматического разбиения СМСок.
*/