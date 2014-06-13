#if !defined(AFX_OUTCOMINGRS_H__CCCA68E2_EE5C_40CF_A063_8123530CF153__INCLUDED_)
#define AFX_OUTCOMINGRS_H__CCCA68E2_EE5C_40CF_A063_8123530CF153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutcomingRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutcomingRS recordset

class COutcomingRS : public CRecordset{
public:
	COutcomingRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COutcomingRS)

// Field/Param Data
	//{{AFX_FIELD(COutcomingRS, CRecordset)
	CString	m_Body;
	BOOL	m_CheckDelivery;
	CString	m_DestPhone;
	BOOL	m_DirectDisplay;
	CTime	m_EndTime;
	long	m_ID;
	long	m_JobStatus;
	long	m_LastError;
	CString	m_Sender;
	CTime	m_SentTime;
	CTime	m_StartTime;
	BYTE	m_AttDone;
	BYTE	m_ContentType;
	CString	m_SmscMsgID;
	//-41
	CString m_DeliverRoute;
	//}}AFX_FIELD

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutcomingRS)
	public:
	virtual CString GetDefaultConnect();	//Default connection string
	virtual CString GetDefaultSQL();		//Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTCOMINGRS_H__CCCA68E2_EE5C_40CF_A063_8123530CF153__INCLUDED_)