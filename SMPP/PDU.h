////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDU.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-16
//	2008-07-16 - //91
//		Add in Initialize method "boost::shared_ptr<AsyncSocket> inSocket" patrameter due to
//		process realisation of abbility working with 2 sockets
//	2008-07-19 - //91
//		Delete parameter "SP<ISMPPSessionState> state" from method ProcessState(), because it redundant.
//		It is sucsesfully accessible by "m_pSocket->getSessionState()"
//
//		Add method ProcessState() to macros PDU_BASICS_DECLARATION.
//	2008-07-20 - //91
//		Add method SetInSocket (boost::shared_ptr<AsyncSocket> inSocket)
////////////////////////////////////////////////////////

#pragma once

#include "../HuSMPPshared.h"

#include "../Utils/rawbuffer.h"
#include "PDUHeader.h"
#include "PDUEventHandler.h"
#include "../Common/Actions/nullaction.h"
#include "PDUOptionalParameters.h"

#include "../Socket/AsyncSocket.h"

#include <boost/shared_ptr.hpp>
////////////////////////////////////////////////////////

class IPDU{
public:
	virtual void Initialize( CH<IRawBuffer> rawBuffer, boost::shared_ptr<AsyncSocket> inSocket ) = 0;
	virtual CH<IRawBuffer> GetRawData() = 0;

	virtual boost::shared_ptr<AsyncSocket> GetInSocket() { return m_pSocket; };
	virtual void SetInSocket ( boost::shared_ptr<AsyncSocket> inSocket ) { m_pSocket = inSocket; };

	virtual CH<IAction> ProcessState() = 0;
	//-72My для процессинга PDU
	virtual void ProcessPDUEventIn( SP<PDUEventHandler> EventHandler ) = 0;
	virtual void ProcessPDUEventOut( SP<PDUEventHandler> EventHandler ) = 0;

	virtual DWORD GetCommandId() = 0;
	virtual const PDUHeader& GetHeader() = 0;
	virtual DWORD GetSequenceNumber() = 0;
	virtual void SetSequenceNumber( DWORD newSequenceNumber ) = 0;
	virtual void SetResultCode( DWORD result ) = 0;
	virtual CH<IPDUOptionalParameters> GetOptionalParameters() = 0;
	virtual void SetOptionalParameters( CH<IPDUOptionalParameters> optionalParams ) = 0;

protected:
	boost::shared_ptr<AsyncSocket> m_pSocket;

DECLARE_CH_REFCOUNTING( IPDU )
};

////////////////////////////////////////////////////////
// useful macroses to define different PDUs
////////////////////////////////////////////////////////
#define PDU_BASICS_DECLARATION \
public: \
	virtual DWORD GetCommandId(); \
	virtual const PDUHeader& GetHeader(); \
	virtual DWORD GetSequenceNumber(); \
	virtual void SetSequenceNumber( DWORD newSequenceNumber ); \
	virtual void SetResultCode( DWORD result ); \
	virtual CH<IPDUOptionalParameters> GetOptionalParameters(); \
	virtual void SetOptionalParameters( CH<IPDUOptionalParameters> optionalParams ); \
	CH<IAction> ProcessState(); \
private: \
	PDUHeader m_Header; \
	CH<IPDUOptionalParameters> m_OptionalParams; \
    bool IsOnlyHeader() { return ( m_Header.command_length == sizeof( m_Header ) ); } \

////////////////////////////////////////////////////////
#define PDU_BASICS_DEFINITION( Type ) \
	DWORD Type::GetCommandId() { return m_Header.command_id; } \
	const PDUHeader& Type::GetHeader() { return m_Header; } \
	DWORD Type::GetSequenceNumber() { return m_Header.sequence_number; } \
	void Type::SetSequenceNumber( DWORD newSequenceNumber ) { m_Header.sequence_number = newSequenceNumber; } \
	void Type::SetResultCode( DWORD result ) { m_Header.command_status = result; } \
	CH<IPDUOptionalParameters> Type::GetOptionalParameters() { return m_OptionalParams; } \
	void Type::SetOptionalParameters( CH<IPDUOptionalParameters> optionalParams ) { m_OptionalParams = optionalParams; } \
	CH<IAction> Type::ProcessState(){ return m_pSocket->getSessionState()->Process( this ); } \


////////////////////////////////////////////////////////
#define PDU_BASICS_DEFINITION_VIRTUAL_STUB( Type ) \
	DWORD Type::GetCommandId() { return m_Header.command_id; } \
	const PDUHeader& Type::GetHeader() { return m_Header; } \
	DWORD Type::GetSequenceNumber() { return m_Header.sequence_number; } \
	void Type::SetSequenceNumber( DWORD newSequenceNumber ) { m_Header.sequence_number = newSequenceNumber; } \
	void Type::SetResultCode( DWORD result ) { m_Header.command_status = result; } \
	CH<IPDUOptionalParameters> Type::GetOptionalParameters() { return m_OptionalParams; } \
	void Type::SetOptionalParameters( CH<IPDUOptionalParameters> optionalParams ) { m_OptionalParams = optionalParams; } \

// =================== END OF FILE =====================
////////////////////////////////////////////////////////