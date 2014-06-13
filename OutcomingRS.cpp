// OutcomingRS.cpp : implementation file
//

#include "stdafx.h"
#include "SMPPSample.h"
#include "OutcomingRS.h"

/////////////////////////////////////////////////////////////////////////////
// COutcomingRS

IMPLEMENT_DYNAMIC(COutcomingRS, CRecordset)

COutcomingRS::COutcomingRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COutcomingRS)
	m_Body = _T("");
	m_CheckDelivery = FALSE;
	m_DestPhone = _T("");
	m_DirectDisplay = FALSE;
	m_ID = 0;
	m_JobStatus = 0;
	m_LastError = 0;
	m_Sender = _T("");
	m_AttDone = 0;
	m_ContentType = 0;
	//-41
	CString m_DeliveryRoute;
//-41	m_nFields = 14;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString COutcomingRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=NVSMSService");
}

CString COutcomingRS::GetDefaultSQL()
{
	return _T("[dbo].[NVSMSOutcoming]");
}

void COutcomingRS::DoFieldExchange(CFieldExchange* pFX)
{
/*
void RFX_Text( CFieldExchange* pFX, const char* szName, CString& value, 
int nMaxLength = 255, int nColumnType = SQL_VARCHAR, short nScale = 0 );
*/
	//{{AFX_FIELD_MAP(COutcomingRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Body]"), m_Body, 4096);
	RFX_Bool(pFX, _T("[CheckDelivery]"), m_CheckDelivery);
	RFX_Text(pFX, _T("[DestPhone]"), m_DestPhone);
	RFX_Bool(pFX, _T("[DirectDisplay]"), m_DirectDisplay);
	RFX_Date(pFX, _T("[EndTime]"), m_EndTime);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[JobStatus]"), m_JobStatus);
//-70	RFX_Byte(pFX, _T("[LastError]"), m_LastError);
	RFX_Long(pFX, _T("[LastError]"), m_LastError);
	RFX_Text(pFX, _T("[Sender]"), m_Sender);
	RFX_Date(pFX, _T("[SentTime]"), m_SentTime);
	RFX_Date(pFX, _T("[StartTime]"), m_StartTime);
	RFX_Byte(pFX, _T("[AttDone]"), m_AttDone);
	RFX_Byte(pFX, _T("[ContentType]"), m_ContentType);
	RFX_Text(pFX, _T("[SmscMsgID]"), m_SmscMsgID);
	//-41
	RFX_Text(pFX, _T("[DeliverRoute]"), m_DeliverRoute);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COutcomingRS diagnostics

#ifdef _DEBUG
void COutcomingRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void COutcomingRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
