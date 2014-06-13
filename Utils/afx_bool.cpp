////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: afx_bool.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus)
// Created	: 2008-09-05
// AFX compatibility layer fo handling bool values.
//
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "afx_bool.h"

////////////////////////////////////////////////////////

void
AFXAPI DDX_Check(CDataExchange* pDX, int nIDC, bool& value){
int ttt = (int)value;
::DDX_Check(pDX, nIDC, ttt);
#pragma warning(push)
#pragma warning(disable:4800)
value = ttt;
#pragma warning( pop )
}