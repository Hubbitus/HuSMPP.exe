////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMSCConfig.cpp
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-18
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
//
//	2008-08-28
//	- Added DeliveryFormat field
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include "HuSMPPshared.h"

////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>

////////////////////////////////////////////////////////

class SMSCConfig{
public:
	SMSCConfig(
		const bool bTransceiver,
		const std::string& remoteHost,
		const std::string& remotePort,
		const std::string& systemId,
		const std::string& password,
		const std::string& systemType,
		const std::string strDeliveryFormat,
		const BYTE nSrcTON = 1, const BYTE nSrcNPI = 1, const BYTE nDestTON = 1, const BYTE nDestNPI = 0
	);

	//Copy ctor
	SMSCConfig(const SMSCConfig& Original);

	virtual const bool isTransceiver() const { return m_bTranceiver; };
	virtual const bool hasTransmitter() const { return !isTransceiver(); };

	virtual const bool getCloseConnectAfterUnbind(){ return m_bCloseConnectAfterUnbind; };
	virtual void setCloseConnectAfterUnbind(bool newVal){ m_bCloseConnectAfterUnbind = newVal; };

	virtual const std::string& GetSystemId() const;
	virtual const std::string& GetPassword() const;
	virtual const std::string& GetSystemType() const;

	virtual const std::string& GetServerAddr() const;
	virtual const std::string& GetServerPort() const;

	virtual const BYTE getSrcTON () const { return m_nSrcTON; }
	virtual const BYTE getSrcNPI () const { return m_nSrcNPI; }
	virtual const BYTE getDestTON () const { return m_nDestTON; }
	virtual const BYTE getDestNPI () const { return m_nDestNPI; }

	virtual void setSrcTON (BYTE val) { m_nSrcTON = val; }
	virtual void setSrcNPI (BYTE val) { m_nSrcNPI = val; }
	virtual void setDestTON (BYTE val) { m_nDestTON = val; }
	virtual void setDestNPI (BYTE val) { m_nDestNPI = val; }

	virtual const std::string& GetDeliveryFormat( ) const { return m_strDeliveryFormat; };
	virtual void SetDeliveryFormat( std::string newStr ) { m_strDeliveryFormat = newStr; };

	virtual boost::shared_ptr<SMSCConfig> clone() const;

private:
	bool m_bTranceiver;

	std::string m_SystemId;
	std::string m_Password;
	std::string m_SystemType;

	std::string m_ServAddr;
	std::string m_ServPort;

	BYTE m_nSrcTON;
	BYTE m_nSrcNPI;
	BYTE m_nDestTON;
	BYTE m_nDestNPI;

	std::string m_strDeliveryFormat;

	bool m_bCloseConnectAfterUnbind;
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////