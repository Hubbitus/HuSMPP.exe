////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : singleton.cpp
// Rewritten in HuSMPP by 
//			Pavel Alexeev (Pahan-Hubbitus) 2008-07-21
// ....
//	2008-07-21 //92
//	- Add method "const ESMEConstNames* GetESMEConstNames()" realisation
//
//	2008-09-05
//	- Move create instances of used items in constructor. There are all used
//		in typical application session, so, it is useless to check it every time.
//		And delete all in destructor.
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "singleton.h"
#include "../../Common/CmnHdr.h"

////////////////////////////////////////////////////////
CSingleton::CSingleton() : m_pLog (new Log()), m_pESMEConstNames(new ESMEConstNames()){
}

////////////////////////////////////////////////////////
CSingleton::~CSingleton(){
	if ( m_pLog != 0 ){
	delete m_pLog;
	m_pLog = 0;
	}
	if ( m_pESMEConstNames != 0 ){
	delete m_pESMEConstNames;
	m_pESMEConstNames = 0;
	}
	if ( m_Instance != 0 ){
	delete m_Instance;
	m_Instance = 0;
	}
}

////////////////////////////////////////////////////////
// function to access to instance
SP<CSingleton>
CSingleton::GetInstance(){
return m_Instance;
}

////////////////////////////////////////////////////////
Log*
CSingleton::GetLog(){
return (Log*)m_pLog;
}

////////////////////////////////////////////////////////
ESMEConstNames*
CSingleton::GetESMEConstNames(){
return m_pESMEConstNames;
}

////////////////////////////////////////////////////////
void
CSingleton::Make(){
//	if ( m_Instance == 0 ){
//	m_Instance = new CSingleton();
//	}
}

////////////////////////////////////////////////////////
void 
CSingleton::Destroy(){
//2008-09-05
//	if ( m_Instance != 0 ){
//	delete m_Instance;
//	m_Instance = 0;
//	}
}

////////////////////////////////////////////////////////
CSingleton* CSingleton::m_Instance = new CSingleton();

// =================== END OF FILE =====================
////////////////////////////////////////////////////////