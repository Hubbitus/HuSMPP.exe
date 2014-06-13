////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMPPMainWindow.cpp
// Modyfied by Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
//
//	2008-08-29
//	- Replace many useless settings-parameters (like m_nDestTON, m_nDestNPI, m_nSrcTON, m_nSrcNPI) what was directly copied from SMSCParams.
//	- Commentout //?-	DDX_Text(pDX, IDC_ADDRESSRANGE,	m_strAddressRange);
//
//	2008-09-10
//	- Add e->Delete(); in anywhere where catched CDBException
//
//	2008-09-11
//	- Inicialisation of family m_n*Cnt and m_strLastTimerString moved to constructor-inicilize fase instead of body.
//	- Added inicialisation m_nDeliveredCntOk and m_nDeliveredCntBad instead of m_nDeliveredCnt
//
//	2008-09-16
//	- (//S!) ГРЯЗНЫЙ, ВРЕМЕННЫЙ ХАК. Пока не реализован синхронны режим.
//
//	2008-09-19
//	- Add method OnSocketConnected.
//	- Correct buttons Connect/Disconnect availability.
//	- Remove call OnDisconnect() from OnSocketDisconnect. And add buttons handling to OnSocketDisconnect.
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HuSMPPshared.h"

#include "Common/Singles/singleton.h"

#include "SMPPSample.h"
#include "SMPPMainWindow.h"
#include "ExtraSettingsDialog.h"
#include "SendSMSDlg.h"

#include "OutcomingRS.h"
#include "SMSCParams.h"

#include "SMS/InSMS.h"
#include "SMS/Delivery.h"
#include "SMS/OutSMS.h"

/////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

/////////////////////////////////////////////////////////////////////////////
CSMPPMainWindow::CSMPPMainWindow(CWnd* pParent /*=NULL*/, int SMSCID)
: CDialog(CSMPPMainWindow::IDD, pParent), m_SMSCID (SMSCID), m_SMSCParams(&m_DBIn)
, m_nDeliveredCntOk(0), m_nDeliveredCntBad(0), m_nSentWithoutDeliveryCnt(0), m_nSentWithDeliveryCnt(0), m_nErrorCnt(0)
, m_strLastTimerString(_T(""))
{

	InitializeCriticalSection( &m_log_cs );
	//Инициализация глобального лога, чтобы дальше его все могли использовать
	GETLOG->initialise(this, IDC_LOG, m_SMSCID, &m_log_cs);

	//Инициализаия кеша, чтобы он мог сюда слать сообщения
	GETRESPCACHE->Initialize(this);

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_tLastReconnect = CTime(2005,1,1,0,0,0);
}

///////////////////////////////////////////////////////////////
CSMPPMainWindow::~CSMPPMainWindow(){
DeleteCriticalSection( &m_log_cs );
}

///////////////////////////////////////////////////////////////
void
CSMPPMainWindow::DoDataExchange(CDataExchange* pDX){
EnterCriticalSection( &m_log_cs );

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSMPPMainWindow)
	DDX_Check(pDX, IDC_TRANSCEIVER,	m_SMSCParams.m_bTransceiver);
	DDX_Text(pDX, IDC_PORT,			m_SMSCParams.m_nPort);
	DDX_Text(pDX, IDC_ADDRESS,		m_SMSCParams.m_strAddress);
	DDX_Text(pDX, IDC_SYSTEMID,		m_SMSCParams.m_strSystemId);
	DDX_Text(pDX, IDC_PASSWORD,		m_SMSCParams.m_strPassword);
	DDX_Text(pDX, IDC_SYSTEMTYPE,	m_SMSCParams.m_strSystemType);
	DDX_Text(pDX, IDC_VERSION,		m_SMSCParams.m_nVersion);
//?-	DDX_Text(pDX, IDC_ADDRESSRANGE,	m_strAddressRange);

	DDX_Text(pDX, IDC_DSTADDRTON, m_SMSCParams.m_nDestTON);
	DDX_Text(pDX, IDC_DSTADDRNPI, m_SMSCParams.m_nDestNPI);
	DDX_Text(pDX, IDC_SRCADDRTON, m_SMSCParams.m_nSrcTON);
	DDX_Text(pDX, IDC_SRCADDRNPI, m_SMSCParams.m_nSrcNPI);

/*
	DDX_Text(pDX, IDC_EDIT_DELIVERED,			m_nDeliveredCnt);
	DDX_Text(pDX, IDC_EDIT_RECEIVED,			m_nReceivedCnt);
	DDX_Text(pDX, IDC_EDIT_SENT_NODELIVERY,		m_nSentWithoutDeliveryCnt);
	DDX_Text(pDX, IDC_EDIT_SENT_WITHDELIVERY,	m_nSentWithDeliveryCnt);
	DDX_Text(pDX, IDC_EDIT_ERRORS,				m_nErrorCnt);
*/
	DDX_Text(pDX, IDC_STATIC_LAST_TIMER,		m_strLastTimerString);
	//}}AFX_DATA_MAP

LeaveCriticalSection( &m_log_cs );	
}

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSMPPMainWindow, CDialog)
	//{{AFX_MSG_MAP(CSMPPMainWindow)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnDoConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	ON_WM_TIMER()
	ON_COMMAND(WM_SMPP_SOCKET_CLOSED, OnSocketClosed)
	ON_COMMAND(WM_SMPP_SOCKET_CONNECTED, OnSocketConnected)
	ON_COMMAND(WM_SMPP_BINDED, OnBinded)
	ON_COMMAND(WM_WRITE_WINDOW_LOG, OnWriteWindowLog)
	ON_COMMAND(WM_SMPP_MESSAGE_RECIVED, OnSMSCMessageReceived)
	ON_COMMAND(WM_SMPP_SUBMIT_RESP_SENDED, OnSMSCMessageRespSended)
	ON_COMMAND(WM_SMPP_SUBMIT_RESP_FAILED, OnSMSCMessageRespFailed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMPPMainWindow message handlers
BOOL
CSMPPMainWindow::OnInitDialog(){
CDialog::OnInitDialog();

// Set the icon for this dialog.  The framework does this automatically
//  when the application's main window is not a dialog
SetIcon(m_hIcon, TRUE);			// Set big icon
SetIcon(m_hIcon, FALSE);		// Set small icon

DBconnect();

	// Initialization from DB
	// now read settings from database
	TRY{
	m_SMSCParams.m_nParams = 0;
	m_SMSCParams.m_strFilter.Format("SMSCID = %d", m_SMSCID);

		if(m_SMSCParams.Open(CRecordset::dynaset, NULL, CRecordset::executeDirect)){
			if(!m_SMSCParams.IsEOF()){
			m_SMSCParams.Close(); //All done, values cached.
			}
			else{
			// cannot find parameter set for this SMSCID
			CString tmp;
			tmp.Format("Cannot find connection params for SMSCID = %d", m_SMSCID);
			AfxMessageBox(tmp);
			GETLOG->AddToLog(tmp);
			m_SMSCParams.Close();
			return false;
			}
		}
		else{
		// cannot open params database
		AfxMessageBox("Cannot open connection parameters database");
		GETLOG->AddToLog("Cannot open connection parameters database");
		return false;
		}
	}
	CATCH (CDBException, e){
		if (m_SMSCParams.IsOpen()) m_SMSCParams.Close();
	AfxMessageBox("Exception on opening connection parameters table" + e->m_strError);
	e->Delete();
	}
	END_CATCH 

::EnableWindow(GetDlgItem(IDC_CONNECT)->GetSafeHwnd(), TRUE);
::EnableWindow(GetDlgItem(IDC_DISCONNECT)->GetSafeHwnd(), FALSE);

SetWindowText(m_SMSCParams.m_strWindowTitle);

UpdateData(FALSE);

GETLOG->AddToLog("Start service\r\n*****************************************");

m_SMPP = boost::shared_ptr<HuSMPPClient> (
	new HuSMPPClient(
		boost::shared_ptr<SMSCConfig>(
			new SMSCConfig(
				m_SMSCParams.m_bTransceiver,
				std::string(m_SMSCParams.m_strAddress), boost::lexical_cast<std::string>(m_SMSCParams.m_nPort), std::string(m_SMSCParams.m_strSystemId), std::string(m_SMSCParams.m_strPassword), std::string(m_SMSCParams.m_strSystemType),
				std::string(m_SMSCParams.m_strDeliveryFormat),
				m_SMSCParams.m_nSrcTON, m_SMSCParams.m_nSrcNPI, m_SMSCParams.m_nDestTON, m_SMSCParams.m_nDestNPI
			)
		)
	)
);
//-57
m_SMPP->SetMessageHandler(this);

// establish connection
OnDoConnect();

// remember this time
m_tLastReconnect = CTime::GetCurrentTime();

return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void
CSMPPMainWindow::OnPaint(){
	if (IsIconic()){
	CPaintDC dc(this); // device context for painting

	SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

	// Center icon in client rectangle
	int cxIcon = GetSystemMetrics(SM_CXICON);
	int cyIcon = GetSystemMetrics(SM_CYICON);
	CRect rect;
	GetClientRect(&rect);
	int x = (rect.Width() - cxIcon + 1) / 2;
	int y = (rect.Height() - cyIcon + 1) / 2;

	// Draw the icon
	dc.DrawIcon(x, y, m_hIcon);
	}
	else{
	CDialog::OnPaint();
	}
}

/////////////////////////////////////////////////////////////////////////////
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR
CSMPPMainWindow::OnQueryDragIcon(){
return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnDoConnect(){
UpdateData(TRUE);

KillTimer(TimerID);//Stop timer to disable repeated reconnect

CWaitCursor wait;

	// Try to connect to the SMSC
	try{
	m_SMPP->Disconnect(); //Enshurance
	m_SMPP->Connect();
	}
	catch (ConnectFailed cf){
	GETLOG->AddToLog(("Connection to SMSC failed. (" + cf.GetDescription()  + ")").c_str() );
	return;
	}

m_SMPP->SetKeepAliveInterval(m_SMSCParams.m_nReconnectTime);

//Result in OnBinded

::EnableWindow(GetDlgItem(IDC_CONNECT)->GetSafeHwnd(), FALSE);
}

/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnBinded(){
	if (m_SMPP->isBinded()){//If used more than 1 socket, this is invoked also not once!
	// init timer for 5 seconds
	GETLOG->AddToLog( "Connection to SMSC sucseeded. Start timer." );
	m_Timer = SetTimer(TimerID, 5000, 0);
	::EnableWindow(GetDlgItem(IDC_CONNECT)->GetSafeHwnd(), FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnDisconnect(){
CWaitCursor wait;

GETLOG->AddToLog ( "CSMPPMainWindow::OnDisconnect(), Disconnecting" );

	if (m_SMPP){
		if (m_SMPP->isBinded())
		m_SMPP->SMSCUnBind(true); //Disconnect after unbind
		else
		m_SMPP->Disconnect();
	}

::EnableWindow(GetDlgItem(IDC_DISCONNECT)->GetSafeHwnd(), FALSE);
KillTimer(TimerID); //Stop timer to disable reconnect
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnSend(){
// Open dialog for sending SMS
CSendSMSDlg dlg(m_SMPP, this);
dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
BEGIN_EVENTSINK_MAP(CSMPPMainWindow, CDialog)
    //{{AFX_EVENTSINK_MAP(CSMPPMainWindow)
//-23	ON_EVENT(CSMPPMainWindow, IDC_SMPP1, 1 /* SMSCMessageNotification */, OnSMSCMessageNotificationSmpp1, VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_DATE VTS_BSTR)
//-23	ON_EVENT(CSMPPMainWindow, IDC_SMPP1, 2 /* SMSCMessageReceived */, OnSMSCMessageReceivedSmpp1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_DATE VTS_DATE)
//-23	ON_EVENT(CSMPPMainWindow, IDC_SMPP1, 3 /* SocketClosed */, OnSocketClosedSmpp1, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// An incoming message was received
afx_msg void
CSMPPMainWindow::OnSMSCMessageReceived(){
CH<IPDUIterator> SMSs = GETSMSCACHE->GetAllCachedPDUs();//После этого КЕШ очистится сам!

	while (SMSs->More()){
	CString SQL;
	std::string strBuffer;

		if ( SafeDynamicCastCH<IPDUDeliverSm, IPDU>(SMSs->Peek())->isDeliveryNotification()){//+82 УВЕДОМЛЕНИЕ
			try{
			boost::shared_ptr<Delivery> deliv = boost::shared_ptr<Delivery>( new Delivery(SafeDynamicCastCH<IPDUDeliverSm, IPDU>(SMSs->Next()), std::string(m_SMSCParams.m_strDeliveryFormat) ) );

			//Увеличиваем счетчик доставленных в окне
				if ( deliv->GetStat()->GetRealValue() == deliv->GetStat()->DELIVERED)
				SMSDeliveredOk();
				else
				SMSDeliveredBad();

			strBuffer = (
				boost::format("DeliveryRcpt received: State: %1%(%2%), MsgID=\"%3%\"%4%, Err=%5%, Text=\"%6%\"")
				% deliv->GetStat()->GetSymbolicName()
				% deliv->GetStat()->GetRealValue()
				% deliv->GetID()
				% (deliv->GetSubAddress().empty() ? "" : "(" + deliv->GetSubAddress() + ")")
				% deliv->GetErr()
				% deliv->GetText()
			).str();

			SQL.Format(
				"EXEC dbo.SMSDelivered @msgID = '%s', @status = %d, @err = '%d', @text = '%s'"
				,deliv->GetID().c_str()
				,deliv->GetStat()->GetRealValue()
//				,( deliv->GetStat()->GetRealValue() == deliv->GetStat()->DELIVERED ? JobStatus_DeliveryOk : JobStatus_DeliveryError )
				,boost::lexical_cast<int>(deliv->GetErr())
				,deliv->GetShortMessageSQlEscaped().c_str() //Full MESSAGE text
			);

				//Все что записалось в лог когда парсилось
				if (! deliv->GetLog().empty())
				strBuffer += (boost::format(" [%1%]") % deliv->GetLog()).str();
			}
			catch(DeliveryFormatError * dfe){
			GETLOG->AddToLog( ("!!!ERROR:" + dfe->GetDescription()).c_str());
			}
		}
		else{//+82 Обычная SMS
		boost::shared_ptr<InSMS> sms = boost::shared_ptr<InSMS>( new InSMS(SafeDynamicCastCH<IPDUDeliverSm, IPDU>(SMSs->Next())) );

		//Увеличиваем счетчик пришедших в окне
		SMSReceived();
		strBuffer += (
			boost::format("!!!Message received: From: \"%s\" %s; To: \"%s\"; DCS=%d(0x%X); esm_class = %d(0x%X);%sText:\"%s\"")
			% sms->GetSourceAddr()
			% (m_SMSCParams.m_bDoDeliverRoute ? '(' + sms->GetOptionalParameterStr(PDU_OPT_DeliverRoute) + ')' : "")
			% sms->GetDestinationAddr()
			% sms->GetDataCoding() % sms->GetDataCoding()
			% sms->GetEsmClass() % sms->GetEsmClass()
			% ENDLINE
			% sms->GetShortMessage()
		).str();

		// write SMS to DB
	    SQL.Format(
			"INSERT INTO NVSMSIncoming \
				(SMSCID, DeliverRoute, Sender, DestPhone, lOption, Body, PartNum, PartTotal, LinkID, SentTime, JobStatus) \
				VALUES(%d, '%s', '%s', '%s', %d, '%s', %d, %d, %d, GetDate(), %d)"
			,m_SMSCID
			,(m_SMSCParams.m_bDoDeliverRoute ? sms->GetOptionalParameterStr(PDU_OPT_DeliverRoute).c_str() : "")
			,sms->GetSourceAddr().c_str()
			,sms->GetDestinationAddr().c_str()
			,sms->GetlOption()
			,sms->GetShortMessageSQlEscaped().c_str()
			,sms->GetMsgPartNo()		//PartNum
			,sms->GetMsgPartsTotal()	//PartTotal
			,sms->GetMsgLinkID()		//PartLinkID
			,JobStatus_Wait
			);

			//Все что записалось в лог когда парсилось
			if (! sms->GetLog().empty())
			strBuffer += (boost::format(" [%s]") % sms->GetLog()).str();
		}

	GETLOG->AddToLog(strBuffer.c_str());

		try	{
	    m_DBIn.ExecuteSQL(SQL);
		}
		catch (CDBException* e){
			//Error-handling code get from http://www.sql.ru/forum/actualthread.aspx?tid=67468
			//I'm googling big time, but not found any right way to get error state or error code from RAISERROR
			if(e->m_strError.Left(10) == "@@@Err: 1:"){//This is NON-fatal error from dbo.SMSDelivered SQL procdure
			GETLOG->AddToLog("Error on delivery processing! " + e->m_strError + ") SQL: " + SQL);
			}
			else{//Possibility (ny chance to diffirintiate it in )
			GETLOG->AddToLog("Error on inserting new SMS or delivery into DB (" + e->m_strError + ") SQL: " + SQL);
			e->Delete(); // NOT Needed if used TRY/CATCH macroses instead of regular try/catch blocks, it is do it automaticaly
			//Trying reconnect:
			DBreconnect();
				try	{// try again! Now
				m_DBIn.ExecuteSQL(SQL);
				}
				catch (CDBException* e){
				GETLOG->AddToLog("AGAIN Error on inserting new SMS into DB (" + e->m_strError + ") SQL: " + SQL);
				GETLOG->AddToLog("So, best way is ***STOP WORKING***.");
				e->ReportError();
				e->Delete();
				KillTimer(TimerID); //Stop timer to disable reconnect
				OnDisconnect();
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnClear(){
SetDlgItemText(IDC_LOG, "");
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnClose(){
OnDisconnect();
	
CDialog::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnCancel(){
OnDisconnect();
CDialog::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnSettings(){
CExtraSettingsDialog dlg(m_SMPP);
dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnSocketClosed(){
GETLOG->AddToLog("Socket Closed!");
::EnableWindow(GetDlgItem(IDC_CONNECT)->GetSafeHwnd(), TRUE);
::EnableWindow(GetDlgItem(IDC_DISCONNECT)->GetSafeHwnd(), FALSE);

//DEBUG
//KillTimer(TimerID);
}


/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnSocketConnected(){
static int reConnectCount = 0;

GETLOG->AddToLog("Socket Connected!");
::EnableWindow(GetDlgItem(IDC_DISCONNECT)->GetSafeHwnd(), TRUE);
SetDlgItemText(IDC_STATIC_LAST_CONNECT_TIME, CTime::GetCurrentTime().Format ("%d.%b %H:%M:%S"));
SetDlgItemInt(IDC_STATIC_RECONNECT_COUNT, ++reConnectCount);
}


/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::OnTimer(UINT nIDEvent){
SetDlgItemText(IDC_STATIC_LAST_TIMER, CTime::GetCurrentTime().Format ("%d.%b %H:%M:%S"));



	//DEBUG TEST
	/*
	if (m_SMPP->isConnected()){
		GETLOG->AddToLog("Timer event.");
		m_SMSCParams.m_nReconnectTime = 9;
			if((m_tLastReconnect + CTimeSpan(0,0,m_SMSCParams.m_nReconnectTime/60,m_SMSCParams.m_nReconnectTime%60)) < CTime::GetCurrentTime()){
			CString msg;
			msg.Format("%d seconds delay done. DEBUG Reconnecting...", m_SMSCParams.m_nReconnectTime);
			GETLOG->AddToLog(msg);
////?			OnDisconnect();
//??			OnDoConnect();
			//This will break connection.
			m_SMPP->getReadSocket()->Write((BYTE*)"test");
			m_tLastReconnect = CTime::GetCurrentTime();
			}
	}
	*/
	//\DEBUG TEST




	if(m_SMPP->isBinded()){// if we are connected to SMSC
		//S!
		if (GETRESPCACHE->Size() > 0 ) return;

	//now check for new jobs to send
	COutcomingRS RS(&m_DBOut);

		try{
		RS.m_nParams = 0;
		RS.m_strFilter.Format("JobStatus = 4 AND SMSCID = %d AND StartTime < GetDate() AND EndTime > GetDate()", m_SMSCID);

//		RS.Open(CRecordset::forwardOnly, NULL, CRecordset::executeDirect);
		RS.Open(CRecordset::dynaset, NULL, CRecordset::executeDirect);
//S!			while (!RS.IsEOF()){
		if (!RS.IsEOF()){
//S! Only ONE at the time!
			CH<IOutSMS> FullSMS;
			FullSMS->Initialize(RS, m_SMPP->GetConfig(), m_SMSCParams.m_bDoDeliverRoute, m_SMSCParams.m_nTextMsglen, std::string(m_SMSCParams.m_strSplitType));

			m_SMPP->SubmitMessage(FullSMS);

			RS.Edit();
			RS.m_JobStatus = RS.m_CheckDelivery ? JobStatus_DeliveryWait : JobStatus_Submited;
			RS.m_AttDone++;
			RS.Update();

//S!			RS.MoveNext();
			}
		RS.Close();
		}
		catch (CDBException* e){
		GETLOG->AddToLog("Error checking new job: " + e->m_strError);
		GETLOG->AddToLog("Trying reconnecting...");
		e->Delete();
		//Trying reconnect:
		DBreconnect();
		}
	}
	else {
	GETLOG->AddToLog("Timer event. Not Binded");

		if (m_SMPP->isConnected()){//Not binded, but connected. Most possible bind wait
		GETLOG->AddToLog("Not binded but connected. Wait.");
		}
		else{
			if((m_tLastReconnect + CTimeSpan(0,0,m_SMSCParams.m_nReconnectTime/60,m_SMSCParams.m_nReconnectTime%60)) < CTime::GetCurrentTime()){
			CString msg;
			msg.Format("%d seconds delay done. Reconnecting...", m_SMSCParams.m_nReconnectTime);
			GETLOG->AddToLog(msg);
			OnDoConnect();
			m_tLastReconnect = CTime::GetCurrentTime();
			}
		}
	}

//?? CDialog::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
afx_msg void
CSMPPMainWindow::OnWriteWindowLog(){
//+87 return;

EnterCriticalSection(GETLOG->de.p_cs);
	if (!GETLOG->de.Writed){//Сообщения приходят черти как, может несколько раз подряд
	CString strLogBuffer = "";
	GetDlgItemText(IDC_LOG, strLogBuffer);
	strLogBuffer =	GETLOG->de.data
//					+ ENDLINE
					+ strLogBuffer.Left(10000)
					+ ENDLINE;

	SetDlgItemText(IDC_LOG, strLogBuffer);
	GETLOG->de.Writed = true;
	}
LeaveCriticalSection(GETLOG->de.p_cs);
}

/////////////////////////////////////////////////////////////////////////////
afx_msg	void
CSMPPMainWindow::OnSMSCMessageRespSended(){
	try{ while ( true ){//Возврат по исключению!
	CH<IOutSMS> SendedSMS = GETRESPCACHE->GetSendedSMS();
	CString logMsg;
	CString UpdateSQL;
		//Записываеем в базу, и еще что-то делаем с успешноотправленными СМСками!
		if (SendedSMS->isDeliveryReceiptRequested()){//Если отправлялось с подтверждением доставки
		SMSSendedWithDelivery();

		logMsg.Format("Message for %s successfully sent. ID = %s",
			SendedSMS->GetDestinationAddr().c_str(),
			(SendedSMS->GetPDUs().end() - 1)->second->GetMessageId().c_str());//-64.1 Записываем ПОСЛЕДНЕЕ msgID!!!
		GETLOG->AddToLog(logMsg);

		UpdateSQL.Format("UPDATE NVSMSOutcoming SET JobStatus = %d, LastError = 0, SmscMsgID = '%s' WHERE ID = %d"
			,JobStatus_DeliveryWait
			,(SendedSMS->GetPDUs().end() - 1)->second->GetMessageId().c_str()
			,SendedSMS->GetDB_ID()
		);
		}
		else{//БЕЗ подтверждения доставки
		SMSSendedWithoutDelivery();

		logMsg.Format("Message for %s successfully sent without id",
			SendedSMS->GetDestinationAddr().c_str());
		GETLOG->AddToLog(logMsg);

		UpdateSQL.Format("UPDATE NVSMSOutcoming SET JobStatus = %d, LastError = 0, SentTime = GETDATE() WHERE ID = %d"
			,JobStatus_Ok
			,SendedSMS->GetDB_ID()
		);
		}

	//Так или иначе, надо что-то в лог (в ЛОГ сразу пишем, чтобы вдруг чего с БД не пропало ничего) записать и в БД:
	//Ловим ниже все
	m_DBOut.ExecuteSQL(UpdateSQL);
	}}
	catch (IOutSMS::Empty*){//НОРМАЛЬНОЕ извещение что в КЕШе просто больше нету
	//S!
	OnTimer(TimerID);
	return;
	}
	catch (CDBException* e){
		if (m_DBOut.IsOpen()) m_DBOut.Close();
	GETLOG->AddToLog("CSMPPMainWindow::OnSMSCMessageRespSended() DB ERROR: " + e->m_strError);
	e->Delete();
	return;
	}
}

/////////////////////////////////////////////////////////////////////////////
afx_msg	void
CSMPPMainWindow::OnSMSCMessageRespFailed(){
	try{ while ( true ){//Возврат по исключению!
	//В конце НЕОБХОДИМО вызвать либо CommitError() либо UnCommitError()
	CH<IOutSMS> FailedSMS = GETRESPCACHE->GetFailedSMS();
	CString logMsg;
	CString UpdateSQL;
	//Записываеем в базу, и еще что-то делаем с НЕуспешноотправленными СМСками!
	SMSError();

	IOutSMS::SMSPairVector::iterator fpduI = FailedSMS->GetPDUs().begin();
	//-64.2 Последнюю ошибку запишем в базу
	DWORD lastError = 0;
		while (fpduI != FailedSMS->GetPDUs().end()){//Перебираем все PairPDU
			if (
				(fpduI->second->GetSequenceNumber() != NOT_RESP_SEQ)//Если вообще есть РЕСП
				&&
				(fpduI->second->GetHeader().command_status != 0) //Если он НЕ успешный
				){
				logMsg.Format("!!!Error 0x%lX(%ld) - {%s}, part %d (total %d), sending message for %s"
				,(lastError = fpduI->second->GetHeader().command_status)
				,fpduI->second->GetHeader().command_status
				,ESMEdescription(fpduI->second->GetHeader().command_status).c_str()
				,(FailedSMS->GetPDUs().size() - (FailedSMS->GetPDUs().end() - fpduI))
				,FailedSMS->GetPDUs().size()
				,FailedSMS->GetDestinationAddr().c_str()
			);
			//-64.1 Записываем ПОСЛЕДНЕЕ msgID!!!
			GETLOG->AddToLog(logMsg);
			//-64.2 Надо организовать повтор посылки, или еще какую-то реакцию на ошибки
			}
		++fpduI;
		}
	//-64.2 Пока ВСЕ подтверждаем, сделать разборку по коду ошибки и выбор
	GETRESPCACHE->CommitError();
	//SentTime здесь будет, вместе с JobStatus показывать не время отсылки, а время последней попытки отсылки
	UpdateSQL.Format("UPDATE NVSMSOutcoming SET JobStatus = %d, LastError = %d, SentTime = GETDATE() WHERE ID = %d"
		,JobStatus_SubmitError
		,lastError
		,FailedSMS->GetDB_ID()
	);
	//Так или иначе, надо что-то в лог (в ЛОГ сразу пишем, чтобы вдруг чего с БД не пропало ничего) записать и в БД:
	//Ловим ниже все
	m_DBOut.ExecuteSQL(UpdateSQL);
	}}
	catch (IOutSMS::Empty*){//НОРМАЛЬНОЕ извещение что в КЕШе просто больше нету
	//S!
	OnTimer(TimerID);
	return;
	}
	catch (CDBException* e){
		if (m_DBOut.IsOpen()) m_DBOut.Close();
	GETLOG->AddToLog("CSMPPMainWindow::OnSMSCMessageRespFailed() DB ERROR: " + e->m_strError);
	e->Delete();
	return;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool
CSMPPMainWindow::DBconnect(bool dontMessageBox /* = false */){
	try{
	m_DBIn.SetLoginTimeout(20);
	m_DBIn.SetQueryTimeout(20);
	m_DBOut.SetLoginTimeout(20);
	m_DBOut.SetQueryTimeout(20);
		if (!m_DBIn.OpenEx(czConnectString, CDatabase::noOdbcDialog) || !m_DBOut.OpenEx(czConnectString, CDatabase::noOdbcDialog)){
		//AfxMessageBox("Cannot open database");
		GETLOG->AddToLog("Cannot open database");
		return false;
		}
		else{
		GETLOG->AddToLog("Database opened ok");
		return true;
		}
	}
	catch (CDBException*e){
		if (m_DBIn.IsOpen()) m_DBIn.Close();
		if (m_DBOut.IsOpen()) m_DBOut.Close();
	CString lBuf = "Exception " + e->m_strError;
	GETLOG->AddToLog(lBuf);
		if (!dontMessageBox) AfxMessageBox(lBuf);
	e->Delete();
	return false;
	}
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::DBdisconnect(){
GETLOG->AddToLog("Disconnecting from DataBase");
	if (m_DBIn.IsOpen()) m_DBIn.Close();
	if (m_DBOut.IsOpen()) m_DBOut.Close();
}

/////////////////////////////////////////////////////////////////////////////
void
CSMPPMainWindow::DBreconnect(){
DBdisconnect();
	while (! DBconnect(true)){
	Sleep(DB_RECONNECT_TIME_SECONDS);
	}
}