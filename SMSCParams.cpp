////////////////////////////////////////////////////////
// Project : SMPPSample
// Module  : SendSMSDlg.cpp
// Rewritten in HuSMPP by 
// code generated on 4 окт€бр€ 2006 г., 16:17
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-30
// 	2008-05-20 renamed to HuSMPPClient from HuSMPP
//	2008-08-28
//	- Added DeliveryFormat field
//	- Change inicialization members in constructor create rather than by = sign in constructor body
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMSCParams.h"

#include "HuSMPPshared.h"

////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(SMSCParams, CRecordset)

////////////////////////////////////////////////////////

SMSCParams::SMSCParams(CDatabase* pdb)
	: CRecordset(pdb)
		,m_nSMSCID(0)
		,m_strName("")
		,m_strWindowTitle("")
		,m_strDescription("")
		,m_nNetwork(0)
		,m_nDestTON(0), m_nDestNPI(0), m_nSrcTON(0), m_nSrcNPI(0)
		,m_nVersion(0)
		,m_strAddress("")
		,m_nPort(0)
		,m_strSystemId("")
		,m_strPassword("")
		,m_strSystemType("")
		,m_bTransceiver(FALSE)
	//m_tCreated;
		,m_bInverseStatINOUT(FALSE)
		,m_nMSKDST(0)
		,m_nReconnectTime(0)
		,m_nTextMsglen(0)
		,m_nLongMsgDelay(0)
		,m_bSentIDisHex(FALSE)
		,m_bDeliveryIDisHex(FALSE)
		,m_bDoDeliverRoute(FALSE)
		,m_strDeliveryFormat("")
		,m_strSplitType(""){

m_nFields = 27;
m_nDefaultType = snapshot;

pdb->SetLoginTimeout(10);
pdb->SetQueryTimeout(10);
}

//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString SMSCParams::GetDefaultConnect(){
//??	return _T("DRIVER=SQL Server;SERVER=192.168.55.2;UID=test;PWD=123;APP=Microsoft Office 2003;WSID=WORK;DATABASE=SMS");
	return czConnectString;
}

CString SMSCParams::GetDefaultSQL(){
	return _T("[dbo].[NVSMSCParams]");
}

void SMSCParams::DoFieldExchange(CFieldExchange* pFX){
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[SMSCID]"), m_nSMSCID);
	RFX_Text(pFX, _T("[Name]"), m_strName);
	RFX_Text(pFX, _T("[WindowTitle]"), m_strWindowTitle);
	RFX_Text(pFX, _T("[Description]"), m_strDescription);
	RFX_Byte(pFX, _T("[nNetwork]"), m_nNetwork);
	RFX_Byte(pFX, _T("[send_DestTON]"), m_nDestTON);
	RFX_Byte(pFX, _T("[send_DestNPI]"), m_nDestNPI);
	RFX_Byte(pFX, _T("[send_SrcTON]"), m_nSrcTON);
	RFX_Byte(pFX, _T("[send_SrcNPI]"), m_nSrcNPI);
	RFX_Byte(pFX, _T("[nVersion]"), m_nVersion);
	RFX_Text(pFX, _T("[IPAddress]"), m_strAddress);
	RFX_Long(pFX, _T("[Port]"), m_nPort);
	RFX_Text(pFX, _T("[SystemId]"), m_strSystemId);
	RFX_Text(pFX, _T("[Password]"), m_strPassword);
	RFX_Text(pFX, _T("[SystemType]"), m_strSystemType);
	RFX_Bool(pFX, _T("[Transceiver]"), m_bTransceiver);
	RFX_Date(pFX, _T("[Created]"), m_tCreated);
	RFX_Bool(pFX, _T("[InverseStatINOUT]"), m_bInverseStatINOUT);
	RFX_Long(pFX, _T("[MSKDST]"), m_nMSKDST);
	RFX_Long(pFX, _T("[ReconnectTime]"), m_nReconnectTime);
	RFX_Long(pFX, _T("[TextMsglen]"), m_nTextMsglen);
	RFX_Long(pFX, _T("[LongMsgDelay]"), m_nLongMsgDelay);
	RFX_Bool(pFX, _T("[SentIDisHex]"), m_bSentIDisHex);
	RFX_Bool(pFX, _T("[DeliveryIDisHex]"), m_bDeliveryIDisHex);
	RFX_Bool(pFX, _T("[DoDeliverRoute]"), m_bDoDeliverRoute);
	RFX_Text(pFX, _T("[DeliveryFormat]"), m_strDeliveryFormat);
	RFX_Text(pFX, _T("[SplitType]"), m_strSplitType);
}
/////////////////////////////////////////////////////////////////////////////
// SMSCParams diagnostics
#ifdef _DEBUG
void SMSCParams::AssertValid() const {
CRecordset::AssertValid();
}

void SMSCParams::Dump(CDumpContext& dc) const{
	CRecordset::Dump(dc);
}
#endif //_DEBUG