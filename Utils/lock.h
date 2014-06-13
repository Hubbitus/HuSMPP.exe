////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : lock.h


#ifndef __LOCK_H__
#define __LOCK_H__

////////////////////////////////////////////////////////
//#include "../Common/Singles/singleton.h"

////////////////////////////////////////////////////////
class CLock
{
public:
	CLock(){ InitializeCriticalSection( &m_CS ); }
	~CLock(){ DeleteCriticalSection(&m_CS); }

  void Lock() 
  { 
    EnterCriticalSection( &m_CS ); 
  }
  void Unlock() 
  { 
    LeaveCriticalSection(&m_CS); 
  }

private:
  CRITICAL_SECTION m_CS;
};

////////////////////////////////////////////////////////
class CLocalLock
{
public:
  CLocalLock( CLock& lock ) : m_Lock( &lock ) {
	  m_Lock->Lock();
 }
  ~CLocalLock() {
	  m_Lock->Unlock();
 }

private:
  CLock* m_Lock;
};


#endif

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////
