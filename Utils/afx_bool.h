////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: afx_bool.h
// Author	: Pavel Alexeev (Pahan-Hubbitus)
// Created	: 2008-08-29
// AFX compatibility layer fo handling bool values.
//
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

void
AFXAPI DDX_Check(CDataExchange* pDX, int nIDC, bool& value);

////////////////////////////////////////////////////////
//Class to provide support of bool values exchange instead of BOOL
//RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, bool& value)
//By analogue whith
//RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, BOOL& value)
// It can't be a free function, because 3rd parameter should be the member (http://msdn.microsoft.com/en-us/library/hew62kk1(VS.71).aspx).

/* THIS IS NOT WORKING :(
Need research

class CRecordset_FRX_bool{
private:
	BOOL tmp;
protected:
void
AFXAPI RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, bool& value){
//tmp = (BOOL)value;
tmp = 10;
::RFX_Bool(pFX, szName, tmp);

value = (tmp != 0);
}
};
*/