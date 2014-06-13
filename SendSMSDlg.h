////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SendSMSDlg.h
// Modyfied: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "HuSMPPClient.h"

////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

////////////////////////////////////////////////////////
class CSendSMSDlg : public CDialog{
private:
	boost::shared_ptr<HuSMPPClient> m_pSMPP;

	enum { IDD = IDD_SENDSMS_DIALOG };
	CString	m_strRecipient;
	CString	m_strSender;
	CString	m_strOptions;
	bool	m_bDoDeliverRoute;
	CString	m_strDeliverRoute;
	BYTE	m_nSrcTON;
	BYTE	m_nSrcNPI;
	BYTE	m_nDestNPI;
	BYTE	m_nDestTON;
	CString	m_strMessage;
	bool	m_bCheckDelivery;
	bool	m_bRegisterInDB;
	bool	m_bDirectDisplay;

public:
	CSendSMSDlg(boost::shared_ptr<HuSMPPClient> pSMPP, CWnd* pParent = NULL);   // standard constructor

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendSMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnSend();
	afx_msg void OnChangeMessage();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckDeliverRoute();
	DECLARE_MESSAGE_MAP()
public:
public:
	afx_msg void OnBnClickedCheckregisterindb();
	};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.