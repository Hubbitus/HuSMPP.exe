////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SendSMSDlg.cpp
// Modyfied: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
//
//	2008-09-10
//	- Add e->Delete(); in anywhere where catched CDBException
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMPPSample.h"
#include "HuSMPPshared.h"
#include "SendSMSDlg.h"
#include "Common/Singles/singleton.h"

#include "SMPPMainWindow.h"	// JobStatus_* constants
#include "Utils/stringUtils.h"

////////////////////////////////////////////////////////
CSendSMSDlg::CSendSMSDlg(boost::shared_ptr<HuSMPPClient> pSMPP, CWnd* pParent /*=NULL*/)
	: CDialog(CSendSMSDlg::IDD, pParent), m_pSMPP(pSMPP){
		
m_strRecipient = _T("79052084523");
m_strSender = _T("2300");
m_strOptions = _T("0 - No special options");
m_strDeliverRoute = "";

m_nSrcTON = m_pSMPP->GetConfig()->getSrcTON();
m_nSrcNPI = m_pSMPP->GetConfig()->getSrcNPI();
m_nDestNPI = m_pSMPP->GetConfig()->getDestNPI();
m_nDestTON = m_pSMPP->GetConfig()->getDestTON();
m_strMessage = _T("");

m_bRegisterInDB = true;

m_bCheckDelivery = true;
m_bDirectDisplay = false;
}

////////////////////////////////////////////////////////
void
CSendSMSDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
//{{AFX_DATA_MAP(CSendSMSDlg)
DDX_Text(pDX, IDC_RECIPIENT, m_strRecipient);
DDX_Text(pDX, IDC_SENDER, m_strSender);
DDX_CBString(pDX, IDC_OPTIONS, m_strOptions);
DDX_Text(pDX, IDC_SRCTON, m_nSrcTON);
DDX_Text(pDX, IDC_SRCNPI, m_nSrcNPI);
DDX_Text(pDX, IDC_DESTNPI, m_nDestNPI);
DDX_Text(pDX, IDC_DESTTON, m_nDestTON);
DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
DDX_Check(pDX, IDC_CHECKDELIVERY, m_bCheckDelivery);
DDX_Check(pDX, IDC_CHECKDELIVERROUTE, m_bDoDeliverRoute);
DDX_Text(pDX, IDC_DELIVER_ROUTE, m_strDeliverRoute);
DDX_Check(pDX, IDC_CHECKREGISTERINDB, m_bRegisterInDB);
DDX_Check(pDX, IDC_CHECKDIRECTDISPLAY, m_bDirectDisplay);
//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendSMSDlg, CDialog)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_EN_CHANGE(IDC_MESSAGE, OnChangeMessage)
	ON_BN_CLICKED(IDC_CHECKDELIVERROUTE, &CSendSMSDlg::OnBnClickedCheckDeliverRoute)
	ON_BN_CLICKED(IDC_CHECKREGISTERINDB, &CSendSMSDlg::OnBnClickedCheckregisterindb)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////
// CSendSMSDlg message handlers

////////////////////////////////////////////////////////
void
CSendSMSDlg::OnSend(){
UpdateData(TRUE);
CWaitCursor wait;

	if (m_bRegisterInDB){
	CDatabase DBOutComing;
	//+87+2
	DBOutComing.SetLoginTimeout(10);
	DBOutComing.SetQueryTimeout(10);

	//Open database connection
	CString SQL;
		try{
		DBOutComing.OpenEx(::czConnectString, CDatabase::noOdbcDialog & CRecordset::appendOnly);
		// write SMS to DB
		SQL.Format(
			"INSERT INTO NVSMSOutcoming \
				(SMSCID, DeliverRoute, Sender, DestPhone, ContentType, Body, StartTime, EndTime, JobStatus, DirectDisplay, CheckDelivery) \
				VALUES(%d, '%s', '%s', '%s', %d, '%s', GetDate(), GetDate()+1, %d, %d, %d)"
				,( (CSMPPMainWindow *) m_pParentWnd)->GetSMSCID()
				,(m_bDoDeliverRoute ? m_strDeliverRoute : "")
				,m_strSender
				,m_strRecipient
				,(BYTE)_ttoi(m_strOptions)
				,strUtils::replaceAll(std::string(m_strMessage), "'", "''").c_str()
				,CSMPPMainWindow::JobStatus_Wait
				,m_bDirectDisplay
				,m_bCheckDelivery
				);
		DBOutComing.ExecuteSQL(SQL);
		DBOutComing.Close();
		}
		catch (CDBException* e){
			if (DBOutComing.IsOpen()) DBOutComing.Close();
		CString logBuf;
		logBuf.Format(
			"CSendSMSDlg::OnSend(): DB Exception. Code: %d!!! Exception %s SQL: %s"
			,e->m_nRetCode
			,e->m_strError + ENDLINE
			,SQL
			);
		GETLOG->AddToLog(logBuf);
		AfxMessageBox(logBuf);
		e->Delete();
		}
	}
	else{ //Do NOT register in DB, send manualy
	CH<IOutSMS> FullSMS;
	boost::shared_ptr<SMSCConfig> cnfg = m_pSMPP->GetConfig()->clone();
	cnfg->setDestNPI(m_nDestNPI);
	cnfg->setDestTON(m_nDestTON);
	cnfg->setSrcNPI(m_nSrcNPI);
	cnfg->setSrcTON(m_nSrcTON);

	FullSMS->Initialize(m_strSender, m_strRecipient, std::string(m_strMessage), CTime::GetCurrentTime(), CTime::GetCurrentTime() + CTimeSpan( 0, 1, 0, 0 ),
						cnfg,
						m_bDoDeliverRoute, m_strDeliverRoute, (BYTE)_ttoi(m_strOptions), m_bCheckDelivery,
						/* DirectDisplay /*= false*/ false
	);
	//FullSMS->Initialize(RS, m_bDoDeliverRoute, 160, cnfg);
	m_pSMPP->SubmitMessage(FullSMS);
	}
}

////////////////////////////////////////////////////////
void
CSendSMSDlg::OnChangeMessage(){
UpdateData(TRUE);
CString strBuffer;
strBuffer.Format("%d", m_strMessage.GetLength());
//Update chars counter
SetDlgItemText(IDC_COUNT, strBuffer);
}

////////////////////////////////////////////////////////
BOOL
CSendSMSDlg::OnInitDialog(){
CDialog::OnInitDialog();
//UpdateData(FALSE);

//return FALSE below is required! http://forums.devx.com/showthread.php?t=92004
GetDlgItem(IDC_MESSAGE)->SetFocus();

return FALSE;	//We want set focus to it
//return TRUE;	// return TRUE unless you set the focus to a control
				// EXCEPTION: OCX Property Pages should return FALSE
}

////////////////////////////////////////////////////////
void
CSendSMSDlg::OnBnClickedCheckDeliverRoute(){
//CEdit* dr = (CEdit*) GetDlgItem(IDC_DELIVER_ROUTE);
	if (IsDlgButtonChecked(IDC_CHECKDELIVERROUTE))
	GetDlgItem(IDC_DELIVER_ROUTE)->EnableWindow(true);
	else GetDlgItem(IDC_DELIVER_ROUTE)->EnableWindow(false);

/*
UpdateData(TRUE);
CString strBuf;
strBuf.Format("m_bDoDeliverRoute=%d", m_bDoDeliverRoute);
AfxMessageBox(strBuf);
//Other way
strBuf.Format("m_bDoDeliverRoute=%d", IsDlgButtonChecked(IDC_CHECKDELIVERROUTE));
AfxMessageBox(strBuf);
*/
}

////////////////////////////////////////////////////////
void
CSendSMSDlg::OnBnClickedCheckregisterindb(){
	//Bee in mind: If we add it into DB, we send it in standard
	//cycle and cn't control this parameters separatly from global settings!
	if (IsDlgButtonChecked(IDC_CHECKREGISTERINDB)){
	GetDlgItem(IDC_SRCTON)->EnableWindow(false);
	GetDlgItem(IDC_DESTTON)->EnableWindow(false);
	GetDlgItem(IDC_SRCNPI)->EnableWindow(false);
	GetDlgItem(IDC_DESTNPI)->EnableWindow(false);
	}
	else{
	GetDlgItem(IDC_SRCTON)->EnableWindow(true);
	GetDlgItem(IDC_DESTTON)->EnableWindow(true);
	GetDlgItem(IDC_SRCNPI)->EnableWindow(true);
	GetDlgItem(IDC_DESTNPI)->EnableWindow(true);
	}
}
