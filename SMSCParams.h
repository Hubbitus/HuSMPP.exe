////////////////////////////////////////////////////////
// Project : HuSMPPClient(was SMPPSample)
// Module  : SMSCParams.h
// Modyfied by Pavel Alexeev (Pahan-Hubbitus) 2008-08-29
// // code generated on 4 окт€бр€ 2006 г., 16:17
//
//	2008-08-29
//	- Remove unesed member: 	BYTE	m_DeliveryProcessing
//	- Property m_strIPAddress renamed to m_strAddress
//
//	2008-10-17
//	- Add property CString	m_strSplitType;
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "Utils/afx_bool.h"

////////////////////////////////////////////////////////

class SMSCParams : public CRecordset/*, public CRecordset_FRX_bool */{
public:
	SMSCParams(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SMSCParams)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_nSMSCID;
	CString	m_strName;
	CString	m_strWindowTitle;
	CString	m_strDescription;
	BYTE	m_nNetwork;
	BYTE	m_nAddrTON;
	BYTE	m_nAddrNPI;
	BYTE	m_nVersion;
	CString	m_strAddress;
	long	m_nPort;
	CString	m_strSystemId;
	CString	m_strPassword;
	CString	m_strSystemType;
	BOOL	m_bTransceiver;
	BYTE	m_nDestTON;
	BYTE	m_nDestNPI;
	BYTE	m_nSrcTON;
	BYTE	m_nSrcNPI;
	CTime	m_tCreated;
	BOOL	m_bInverseStatINOUT;
	long	m_nMSKDST;
	long	m_nReconnectTime;
	long	m_nTextMsglen;
	long	m_nLongMsgDelay;
	BOOL	m_bSentIDisHex;
	BOOL	m_bDeliveryIDisHex;
	BOOL	m_bDoDeliverRoute;
	CString	m_strDeliveryFormat;
	CString	m_strSplitType;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};