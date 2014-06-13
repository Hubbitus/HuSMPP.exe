// SMPPSample.h : main header file for the SMPPSAMPLE application
//

#if !defined(AFX_SMPPSAMPLE_H__72765543_5322_42DC_954C_C8002EA5E041__INCLUDED_)
#define AFX_SMPPSAMPLE_H__72765543_5322_42DC_954C_C8002EA5E041__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMPPSampleApp:
// See SMPPSample.cpp for the implementation of this class
//

class CSMPPSampleApp : public CWinApp
{
public:
	CSMPPSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMPPSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMPPSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMPPSAMPLE_H__72765543_5322_42DC_954C_C8002EA5E041__INCLUDED_)
