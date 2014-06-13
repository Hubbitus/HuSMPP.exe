// SMPPSample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SMPPSample.h"
#include "SMPPMainWindow.h"

//TESTS
#include "TESTS/wxDB_DatabaseLayer.h"

/////////////////////////////////////////////////////////////////////////////
// CSMPPSampleApp
BEGIN_MESSAGE_MAP(CSMPPSampleApp, CWinApp)
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMPPSampleApp construction
CSMPPSampleApp::CSMPPSampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSMPPSampleApp object

CSMPPSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSMPPSampleApp initialization

BOOL CSMPPSampleApp::InitInstance()
{
//-79.2	AfxEnableControlContainer();
	CWinApp::InitInstance();

//DEBUG
//-42	
//	AfxMessageBox(_T("TEST"));
//	MessageBox(NULL,"Hello, World!","Test",MB_OK);

	//Снова получение, чтобы с Юникодом не возиться
	//http://www.codeguru.com/forum/showthread.php?t=434533
	//http://www.codeguru.com/forum/showthread.php?t=386406
	m_lpCmdLine = GetCommandLine();
//	AfxMessageBox(CA2T(m_lpCmdLine));
//	AfxMessageBox(m_lpCmdLine);

	//////////////////////////TESTS/////////////////////////
//?	wxDB_DatabaseLayer wxdb;
//?	int t;
	////////////////////////\TESTS/////////////////////////


	int argc = 0;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
		if(argc > 1){
//		AfxMessageBox( CW2A(argv[1]) );
		CSMPPMainWindow dlg (NULL, atoi(CW2A(argv[1])));
		m_pMainWnd = &dlg;

		INT_PTR nResponse = dlg.DoModal();

			if (nResponse == IDOK){
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
			}
			else if (nResponse == IDCANCEL){
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
			}
		}
		else{
		AfxMessageBox("Please enter command-line parameter: SMSCID");
		}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
