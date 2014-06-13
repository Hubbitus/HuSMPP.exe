////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : singleton.h
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-21
// ....
//	2008-07-21 //92
//		Add method "const ESMEConstNames* GetESMEConstNames()" 
//		Add member "ESMEConstNames* m_pESMEConstNames;"
////////////////////////////////////////////////////////

#include "../../HuSMPPshared.h"

class SMS;
class InSMS;
class IOutSMS;

class ISMSCache;
class ISMSRespCache;


#include "../../Utils/log.h"
#include "SMSCache.h"
#include "SMSRespCache.h"
#include "SMPP/ESMEConstNames.h"

////////////////////////////////////////////////////////

class CSingleton{
friend class CLibrary;
public:
	static SP<CSingleton> GetInstance();

//-11  virtual CH<IConfig> GetConfig() { return m_Config; }
	virtual Log* GetLog();
	virtual CH<ISMSCache> GetSMSCache() { return m_Cache; }
	virtual CH<ISMSRespCache> GetRespCache() { return m_CacheResp; }
//-11  virtual CH<IGlobalFunctions> GetGlobalFunctions() { return m_GlobalFunctions; }
	//+92
	virtual ESMEConstNames* GetESMEConstNames();

protected:
	CSingleton();
	virtual ~CSingleton();

	static void Make();
	static void Destroy();

private:
	static CSingleton* m_Instance;

// singles;
//-11  CH<IConfig> m_Config;
	Log* m_pLog;

	CH<ISMSCache> m_Cache;		//Для обмена ПРИШЕДШИМИ СМС
	CH<ISMSRespCache> m_CacheResp;	//Для обмена и сохранения, учета ОТПРАВЛЯЕМЫХ СМС, и ожидания resp'ов на них
//-11  CH<IGlobalFunctions> m_GlobalFunctions;

	//+92
	ESMEConstNames* m_pESMEConstNames;
};

// =================== END OF FILE =====================
////////////////////////////////////////////////////////