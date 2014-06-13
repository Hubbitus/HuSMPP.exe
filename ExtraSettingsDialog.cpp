////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : ExtraSettingsDialog.cpp
// Modyfied: Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ExtraSettingsDialog.h"

////////////////////////////////////////////////////////
CExtraSettingsDialog::CExtraSettingsDialog(boost::shared_ptr<HuSMPPClient> pSMPP, CWnd* pParent /*=NULL*/)
	: CDialog(CExtraSettingsDialog::IDD, pParent), m_pSMPP(pSMPP){
	//{{AFX_DATA_INIT(CExtraSettingsDialog)
	m_dwKeepAlive = 0;
	//}}AFX_DATA_INIT
}

////////////////////////////////////////////////////////
void CExtraSettingsDialog::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtraSettingsDialog)
	DDX_Text(pDX, IDC_KEEPALIVE, m_dwKeepAlive);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtraSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(CExtraSettingsDialog)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtraSettingsDialog message handlers

/////////////////////////////////////////////////////////////////////////////
BOOL CExtraSettingsDialog::OnInitDialog(){
	CDialog::OnInitDialog();

	m_dwKeepAlive = m_pSMPP->GetKeepAliveInterval();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
void CExtraSettingsDialog::OnClose() {
	UpdateData(TRUE);
	m_pSMPP->SetKeepAliveInterval(m_dwKeepAlive);	
	CDialog::OnOK();
}