; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSMPPSampleApp
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SMPPSample.h"

ClassCount=6
Class1=CSMPPSampleApp
Class2=CSMPPSampleDlg

ResourceCount=7
Resource2=IDD_SMPPSAMPLE_DIALOG
Resource3=IDD_EXTRA_DIALOG
Resource1=IDR_MAINFRAME
Class3=CExtraSettingsDialog
Resource4=IDD_SMPPSAMPLE_DIALOG (Englisch (USA))
Resource5=IDD_SENDSMS_DIALOG
Class4=COutcomingRS
Resource6=IDD_SMPPSAMPLE_DIALOG (English (U.S.))
Class5=CSendSMSDlg
Class6=SMSCParams
Resource7=IDD_EXTRA_DIALOG (German (Germany))

[CLS:CSMPPSampleApp]
Type=0
HeaderFile=SMPPSample.h
ImplementationFile=SMPPSample.cpp
Filter=N
LastObject=CSMPPSampleApp

[CLS:CSMPPSampleDlg]
Type=0
HeaderFile=SMPPSampleDlg.h
ImplementationFile=SMPPSampleDlg.cpp
Filter=D
LastObject=CSMPPSampleDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SMPPSAMPLE_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSMPPSampleDlg

[DLG:IDD_SMPPSAMPLE_DIALOG (English (U.S.))]
Type=1
Class=CSMPPSampleDlg
ControlCount=42
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ADDRESS,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PORT,edit,1350639744
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SYSTEMID,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ADDRTON,edit,1350639744
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SYSTEMTYPE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_ADDRNPI,edit,1350639744
Control15=IDC_STATIC,static,1342308352
Control16=IDC_PASSWORD,edit,1350631584
Control17=IDC_STATIC,static,1342308352
Control18=IDC_VERSION,edit,1350639744
Control19=IDC_STATIC,static,1342308352
Control20=IDC_ADDRESSRANGE,edit,1350631552
Control21=IDC_TRANSCEIVER,button,1342242819
Control22=IDC_LOG,edit,1352669316
Control23=IDCANCEL,button,1342242816
Control24=IDC_SETTINGS,button,1342242816
Control25=IDC_CONNECT,button,1342242816
Control26=IDC_DISCONNECT,button,1342242816
Control27=IDC_CLEAR,button,1342242816
Control28=IDC_SMPP1,{DD9F330B-B1C8-4EAB-A30D-2FE6817EB076},1073807360
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EDIT_SENT_NODELIVERY,edit,1350633600
Control33=IDC_EDIT_RECEIVED,edit,1350633600
Control34=IDC_EDIT_DELIVERED,edit,1350633600
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EDIT_SENT_WITHDELIVERY,edit,1350633600
Control37=IDC_STATIC,button,1342177287
Control38=IDC_SEND,button,1342242816
Control39=IDC_STATIC,static,1342308352
Control40=IDC_EDIT_ERRORS,edit,1350633600
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC_LAST_TIMER,static,1342308352

[DLG:IDD_EXTRA_DIALOG]
Type=1
Class=CExtraSettingsDialog
ControlCount=10
Control1=IDC_LICENSE_KEY,edit,1350631552
Control2=IDC_CHECK,button,1342242816
Control3=IDC_CTT,edit,1350631552
Control4=IDC_BROWSE,button,1342242816
Control5=IDOK,button,1342242816
Control6=IDCLOSE,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_KEEPALIVE,edit,1350631552
Control10=IDC_STATIC,static,1342308352

[CLS:CExtraSettingsDialog]
Type=0
HeaderFile=ExtraSettingsDialog.h
ImplementationFile=ExtraSettingsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CExtraSettingsDialog

[DLG:IDD_SMPPSAMPLE_DIALOG (Englisch (USA))]
Type=1
Class=CSMPPSampleDlg
ControlCount=50
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,button,1342177287
Control3=IDC_TCPIP,button,1342308361
Control4=IDC_X25,button,1342177289
Control5=IDC_SINGLEPORT,button,1342242819
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ADDRESS,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_PORT,edit,1350639744
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SYSTEMID,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_ADDRTON,edit,1350639744
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SYSTEMTYPE,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_ADDRNPI,edit,1350639744
Control19=IDC_STATIC,static,1342308352
Control20=IDC_PASSWORD,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_VERSION,edit,1350639744
Control23=IDC_STATIC,static,1342308352
Control24=IDC_ADDRESSRANGE,edit,1350631552
Control25=IDC_TRANSCEIVER,button,1342242819
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308352
Control28=IDC_SRCTON,edit,1350639744
Control29=IDC_DESTTON,edit,1350639744
Control30=IDC_STATIC,static,1342308352
Control31=IDC_SRCNPI,edit,1350639744
Control32=IDC_DESTNPI,edit,1350639744
Control33=IDC_STATIC,static,1342308352
Control34=IDC_RECIPIENT,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_SENDER,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_OPTIONS,combobox,1344339970
Control39=IDC_STATIC,static,1342308352
Control40=IDC_MESSAGE,edit,1352732676
Control41=IDC_COUNT,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_LOG,edit,1352669316
Control44=IDCANCEL,button,1342242816
Control45=IDC_SETTINGS,button,1342242816
Control46=IDC_CONNECT,button,1342242816
Control47=IDC_DISCONNECT,button,1342242816
Control48=IDC_SEND,button,1342242816
Control49=IDC_CLEAR,button,1342242816
Control50=IDC_SMPP1,{DD9F330B-B1C8-4EAB-A30D-2FE6817EB076},1073807360

[DLG:IDD_EXTRA_DIALOG (German (Germany))]
Type=1
Class=CExtraSettingsDialog
ControlCount=10
Control1=IDC_LICENSE_KEY,edit,1350631552
Control2=IDC_CHECK,button,1342242816
Control3=IDC_CTT,edit,1350631552
Control4=IDC_BROWSE,button,1342242816
Control5=IDOK,button,1342242816
Control6=IDCLOSE,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_KEEPALIVE,edit,1350631552
Control10=IDC_STATIC,static,1342308352

[CLS:COutcomingRS]
Type=0
HeaderFile=OutcomingRS.h
ImplementationFile=OutcomingRS.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=COutcomingRS

[DB:COutcomingRS]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[ID], 4, 4
Column2=[SMSCID], -6, 1
Column3=[Sender], 12, 32
Column4=[DestPhone], 12, 32
Column5=[Body], 12, 1024
Column6=[StartTime], 11, 16
Column7=[EndTime], 11, 16
Column8=[SentTime], 11, 16
Column9=[JobStatus], 4, 4
Column10=[DirectDisplay], -7, 1
Column11=[CheckDelivery], -7, 1
Column12=[ContentType], -6, 1
Column13=[LastError], -6, 1
Column14=[AttDone], -6, 1
Column15=[SmscMsgID], 12, 50

[DLG:IDD_SENDSMS_DIALOG]
Type=1
Class=CSendSMSDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SRCTON,edit,1350639744
Control5=IDC_DESTTON,edit,1350639744
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SRCNPI,edit,1350639744
Control8=IDC_DESTNPI,edit,1350639744
Control9=IDC_STATIC,static,1342308352
Control10=IDC_RECIPIENT,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SENDER,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_OPTIONS,combobox,1344339970
Control15=IDC_STATIC,static,1342308352
Control16=IDC_MESSAGE,edit,1352732676
Control17=IDC_COUNT,static,1342308352
Control18=IDC_SEND,button,1342242816

[CLS:CSendSMSDlg]
Type=0
HeaderFile=SendSMSDlg.h
ImplementationFile=SendSMSDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSendSMSDlg

[CLS:SMSCParams]
Type=0
HeaderFile=SMSCParams.h
ImplementationFile=SMSCParams.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=SMSCParams

[DB:SMSCParams]
DB=1
DBType=ODBC
ColumnCount=24
Column1=[SMSCID], 4, 4
Column2=[WindowTitle], 12, 128
Column3=[nNetwork], -6, 1
Column4=[nAddrTON], -6, 1
Column5=[nAddrNPI], -6, 1
Column6=[nVersion], -6, 1
Column7=[IPAddress], 12, 32
Column8=[Port], 4, 4
Column9=[SystemId], 12, 32
Column10=[Password], 12, 32
Column11=[SystemType], 12, 32
Column12=[Transceiver], -7, 1
Column13=[SinglePort], -7, 1
Column14=[send_DestTON], -6, 1
Column15=[send_DestNPI], -6, 1
Column16=[send_SrcTON], -6, 1
Column17=[send_SrcNPI], -6, 1
Column18=[DeliveryProcessing], -6, 1
Column19=[Created], 11, 16
Column20=[ReconnectTime], 4, 4
Column21=[TextMsglen], 4, 4
Column22=[LongMsgDelay], 4, 4
Column23=[SentIDIsHex], -7, 1
Column24=[DeliveryIDisHex], -7, 1

