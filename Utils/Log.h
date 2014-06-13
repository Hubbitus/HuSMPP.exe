//////////////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : Log.cpp
// Author  : Pavel Alexeev
// Rewritten in HuSMPP by Pavel Alexeev 2008-07-30
//	2008-07-30
// - Replace CString anywhere by tstring and boost:::format
//////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////

#include "../HuSMPPshared.h"
#include "../Resource.h"

#include <string>
#include <iostream>
#include <fstream>

//////////////////////////////////////////////////////////////////

struct DataExchange{
	DataExchange() : Writed (false){}
	HWND hWnd; //��� ������� ���������
	CRITICAL_SECTION *p_cs; //��� ������������� ������ �������

	//������, ������������ ����� �������� 
	CString data;  //���������� ������
	bool Writed;//���� ��������, ��������������, ���� ��� - ����������.
};
					
class Log {
private:
	CWnd * m_logWnd;
	HWND m_HWNDlogWnd;

	int m_IDC_LOG;

//-53??????	CLock m_Lock;

	std::ofstream m_LogFile;
	int m_SMSCID; //��� ����� � ����� �����
	CString FileName;
	std::wstring ttt;

	bool m_initialised;

	bool logToWindow;
	bool logToFile;

	CRITICAL_SECTION * cs;
public:
	Log();
	virtual ~Log(void);
	void AddToLog(CString strString, bool logOnlyFile = false);

	//��������� ������� �� �������������
	void initialise (CWnd* logWnd, int TextLogIDX, int SMSCID, CRITICAL_SECTION * log_cs);

	void DisableFileLogging(){ logToFile = false; };
	void EnableWindowLogging(){ logToWindow = true; };
	void EnableFileLogging(){ logToFile = true; };

	//-60 �������� ������
	DataExchange de;
};
