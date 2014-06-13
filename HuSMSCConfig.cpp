////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : SMSCConfig.cpp
// Changed in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-19
// Rewritten in HuSMPPClient by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-05-20
////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Common/CmnHdr.h"

#include "HuSMSCConfig.h"

////////////////////////////////////////////////////////

SMSCConfig::SMSCConfig(
	const bool bTransceiver,
	const std::string& remoteHost,
	const std::string& remotePort,
	const std::string& systemId,
	const std::string& password,
	const std::string& systemType,
	const std::string strDeliveryFormat,
	const BYTE nSrcTON, const BYTE nSrcNPI, const BYTE nDestTON, const BYTE nDestNPI
	)
	: m_bTranceiver(bTransceiver),
		m_SystemId (systemId), m_Password (password), m_SystemType (systemType),
		m_nSrcTON (nSrcTON), m_nSrcNPI (nSrcNPI), m_nDestTON (nDestTON), m_nDestNPI	(nDestNPI),
		m_ServAddr (remoteHost), m_ServPort (remotePort) , m_bCloseConnectAfterUnbind(true), m_strDeliveryFormat(strDeliveryFormat){
}

////////////////////////////////////////////////////////
SMSCConfig::SMSCConfig(const SMSCConfig& orig)
	: m_bTranceiver(orig.isTransceiver()),
		m_SystemId (orig.GetSystemId()), m_Password (orig.GetPassword()), m_SystemType (orig.GetSystemType()),
		m_nSrcTON (orig.getSrcTON()), m_nSrcNPI (orig.getSrcNPI()), m_nDestTON (orig.getDestTON()), m_nDestNPI	(orig.getDestNPI()),
		m_ServAddr (orig.GetServerAddr()), m_ServPort (orig.GetServerPort()), m_strDeliveryFormat(orig.GetDeliveryFormat()){
}

////////////////////////////////////////////////////////
const std::string&
SMSCConfig::GetSystemId() const{
return m_SystemId;
}

////////////////////////////////////////////////////////
const std::string&
SMSCConfig::GetPassword() const{
return m_Password;
}

////////////////////////////////////////////////////////
const std::string& 
SMSCConfig::GetSystemType() const{
return m_SystemType;
}

////////////////////////////////////////////////////////
const std::string&
SMSCConfig::GetServerAddr() const{
return m_ServAddr;
}

////////////////////////////////////////////////////////
const std::string&
SMSCConfig::GetServerPort() const{
return m_ServPort;
}

////////////////////////////////////////////////////////
boost::shared_ptr<SMSCConfig>
SMSCConfig::clone() const{
boost::shared_ptr<SMSCConfig> ret ( new SMSCConfig(*this) );

return ret;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////