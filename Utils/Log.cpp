//////////////////////////////////////////////////////////////////
// Project : HuSMPPSample
// Module  : InSMS.cpp
// Author  : Pavel Alexeev
//////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Log.h"

//////////////////////////////////////////////////////////////////

Log::Log(){
m_initialised = false;
logToWindow = logToFile = true;

m_HWNDlogWnd = 0;
}

Log::~Log(){
}

//////////////////////////////////////////////////////////////////
void
Log::AddToLog(CString strString, bool logOnlyFile){

	if ( !m_initialised ) return;
EnterCriticalSection( cs );

	if (logToFile || (!logOnlyFile && logToWindow)){//Тогда добавляем время
	//Добавляем время
	strString = 
		CTime::GetCurrentTime().Format ("%d.%b %H:%M:%S ") //Время
		+ strString //плюс сама строка лога
		;
		}
	else{
	LeaveCriticalSection ( cs );
	return;
	}

	if (logToFile){
	m_LogFile.open( FileName, std::ios_base::app);
		if (m_LogFile.good()){
		//-76
		m_LogFile << std::endl << strString;
		}
	m_LogFile.close();//Закрываем пока каждый раз, чтобы не потерять ничего в случае зависа!
	}

	if (!logOnlyFile && logToWindow){
	CString strLogBuffer;
		//-56 Инициализация по первому требованию. Каждый раз этого НЕЛЬЗЯ делать! смотри подробное описание 56
		//-56m_HWNDlogWnd = m_logWnd->GetSafeHwnd();
		if (m_HWNDlogWnd == 0) m_HWNDlogWnd = m_logWnd->GetSafeHwnd();

	CWnd* logWindow = 0;

		if ( (logWindow = CWnd::FromHandlePermanent(m_HWNDlogWnd)) != 0 ){/*Если можно вообще в окно писать!
		По крайней мере хоть есть возможность это проверить наконец!
		*/

		//-56.1 CDataExchange dx(logWindow, 1);
		//-56.1 DDX_Text(&dx, m_IDC_LOG, strLogBuffer);
		logWindow->GetDlgItemText(m_IDC_LOG, strLogBuffer);
		
		// В окне весь текст перезаписываем
		strLogBuffer =
			strString
			+ ENDLINE
			+ strLogBuffer.Left(10000);

		logWindow->SetDlgItemText(m_IDC_LOG, strLogBuffer);
		}
		else{
		//Посылаем сообщение, чтобы главный поток записал в окно:
		de.hWnd = m_HWNDlogWnd;
			if (!de.Writed) de.data = strString
									+ ENDLINE
									+ de.data;
			else de.data = strString  + ENDLINE;

		de.Writed = false;
		::PostMessage(de.hWnd,WM_COMMAND, WM_WRITE_WINDOW_LOG,0);
		LeaveCriticalSection(de.p_cs);
		return;
		}
	}

LeaveCriticalSection( cs );
}

//////////////////////////////////////////////////////////////////
void
Log::initialise (CWnd * logWnd, int TextLogIDX, int SMSCID, CRITICAL_SECTION * log_cs){
	//initialise должен вызываться единожды
	chASSERT( !m_initialised );
	if ( m_initialised ) return;

//Критическая секция
cs = log_cs;

m_IDC_LOG = TextLogIDX;
//HWND придется инициализировать позже, поскольку вначале и окна-то нет :(
m_logWnd = static_cast<CWnd*>(logWnd);
m_initialised = true;

//-50
FileName.Format (LOGFILENAME, SMSCID);

//-50 По дефолту и туда и туда писать будем
logToWindow = logToFile = true;

//-60
de.p_cs = log_cs;
}