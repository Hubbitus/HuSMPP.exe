////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : ExtraSettingsDialog.h
// Modyfied: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
////////////////////////////////////////////////////////

#pragma once
////////////////////////////////////////////////////////
#include "HuSMPPshared.h"
#include "resource.h"
#include "HuSMPPClient.h"

#include <boost/shared_ptr.hpp>
/////////////////////////////////////////////////////////////////////////////
// CExtraSettingsDialog dialog
class CExtraSettingsDialog : public CDialog{
public:
	CExtraSettingsDialog(boost::shared_ptr<HuSMPPClient> pSMPP, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CExtraSettingsDialog)
	enum { IDD = IDD_EXTRA_DIALOG };
	long	m_dwKeepAlive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtraSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CExtraSettingsDialog)
	afx_msg void OnApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	boost::shared_ptr<HuSMPPClient> m_pSMPP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.