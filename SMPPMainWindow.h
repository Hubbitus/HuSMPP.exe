////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMPPMainWindow.h
// Modyfied by Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
//
//	@TODO: Replace m_SMSCParams.m_ReconnectTime by something like m_SMSCParams.m_nKeepAlive
//
//	2008-08-29
//	- Replace many useless settings-parameters (like m_nDestTON, m_nDestNPI, m_nSrcTON, m_nSrcNPI) what was directly copied from SMSCParams
//
//	2008-09-08
//	- Added methods: DBconnect(), DBdisconnect(), DBreconnect();
//
//	2008-09-09
//	- In enum
//		JobStatus_Error renamed to JobStatus_SubmitError
//		JobStatus_CheckDeliveryWait and JobStatus_ChckDeliveryOk renamed to JobStatus_DeliveryWait and JobStatus_DeliveryOk accordingly
//
//	2008-09-11
//	- Method SMSDelivered() replaced by 2: SMSDeliveredOk() and SMSDeliveredBad()
//		Accordingly it property m_nDeliveredCnt by: m_nDeliveredCntOk and m_nDeliveredCntBad;
//	- Implementation of methods: SMSError(), SMSSendedWithDelivery(), SMSSendedWithoutDelivery(), SMSDeliveredOk(), SMSDeliveredBad(), SMSReceived()
//		changed from like: SMSError(){ UpdateData(); ++m_nErrorCnt; UpdateData(FALSE); };
//		to like SMSError(){ SetDlgItemInt(++m_nErrorCnt); };
//		And accordingly ot, deleted (comment outed) lines to exchange data in DoDataExchenge method
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "HuSMPPClient.h"
#include "HuSMPPshared.h"
#include "SMPP/PDUEventHandler.h"
#include "SMSCParams.h"

#include <boost/shared_ptr.hpp>

////////////////////////////////////////////////////////

class CSMPPMainWindow : public CDialog{
public:
	CSMPPMainWindow(CWnd* pParent = NULL, int SMSCID = 0);	// standard constructor
	virtual ~CSMPPMainWindow();

	virtual void SetSMSCID(int SMSCID){m_SMSCID = SMSCID;};
	virtual int GetSMSCID(){return m_SMSCID;};

	//{{AFX_DATA(CSMPPMainWindow)
	enum { IDD = IDD_SMPPSAMPLE_DIALOG };
	enum JobStatus { JobStatus_Ok = 2, JobStatus_SubmitError = 3, JobStatus_Wait = 4, JobStatus_DeliveryWait = 5, JobStatus_DeliveryOk = 6, JobStatus_Submited = 7 };

	UINT	m_nDeliveredCntOk;
	UINT	m_nDeliveredCntBad;
	UINT	m_nReceivedCnt;
	UINT	m_nSentWithoutDeliveryCnt;
	UINT	m_nSentWithDeliveryCnt;
	UINT	m_nErrorCnt;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMPPMainWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
	int m_SMSCID;

	boost::shared_ptr<HuSMPPClient>	m_SMPP;

	CTime m_tLastReconnect;
	CString	m_strLastTimerString;

	static const int TimerID = 107;//Random number

	CRITICAL_SECTION m_log_cs;

	HICON m_hIcon;

	CDatabase m_DBOut;
	CDatabase m_DBIn;
	UINT_PTR m_Timer;

	virtual bool DBconnect(bool dontMessageBox = false);
	virtual void DBdisconnect();
	/*
	Small more than just DBdisconnect(); DBconnect();. Will wait connection if it is not 
	sucseeded.
	This is not cooperated with net activity, but STRONGLY RECOMMENDED disconnect from
	SMSC when we have not connection into local DB.
	*/
	virtual void DBreconnect();

	HANDLE mutAllowSendSMS;

	SMSCParams m_SMSCParams;

	virtual void SMSError(){ SetDlgItemInt(IDC_EDIT_ERRORS, ++m_nErrorCnt); };
	virtual void SMSSendedWithDelivery(){ SetDlgItemInt(IDC_EDIT_SENT_WITHDELIVERY, ++m_nSentWithDeliveryCnt); };
	virtual void SMSSendedWithoutDelivery(){ SetDlgItemInt(IDC_EDIT_SENT_NODELIVERY, ++m_nSentWithoutDeliveryCnt); };
//	virtual void SMSDelivered(){ UpdateData(); ++m_nDeliveredCnt; UpdateData(FALSE); };
	virtual void SMSDeliveredOk(){
		SetDlgItemInt(IDC_EDIT_DELIVERED_OK, ++m_nDeliveredCntOk);
		SetDlgItemInt(IDC_EDIT_DELIVERED, m_nDeliveredCntOk + m_nDeliveredCntBad);
	};
	virtual void SMSDeliveredBad(){
		SetDlgItemInt(IDC_EDIT_DELIVERED_BAD, ++m_nDeliveredCntBad);
		SetDlgItemInt(IDC_EDIT_DELIVERED, m_nDeliveredCntOk + m_nDeliveredCntBad);
	};
	virtual void SMSReceived(){ SetDlgItemInt(IDC_EDIT_RECEIVED, ++m_nReceivedCnt); };

	// Generated message map functions
	//{{AFX_MSG(CSMPPMainWindow)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDoConnect();
	afx_msg void OnBinded();
	afx_msg void OnDisconnect();
	afx_msg void OnSend();
	afx_msg void OnChangeMessage();
//-61	void OnSMSCMessageReceivedSmpp1(SP<IPDUDeliverSm> pdu, LPCTSTR bstrDestination, LPCTSTR bstrOriginator, LPCTSTR bstrMessage, long lOption/*, DATE SMSCTimeStamp, DATE Validity*/);
	afx_msg	void OnSMSCMessageReceived();
	afx_msg	void OnSMSCMessageRespSended();//Сообщение что успешно послана СМС
	afx_msg	void OnSMSCMessageRespFailed();//Сообщение что НЕуспешно послана СМС
	afx_msg void OnClear();
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnSocketConnected();
//-57	afx_msg void OnSocketClosedSmpp1(long lReserved);
	afx_msg void OnSocketClosed();
	afx_msg void OnWriteWindowLog();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.