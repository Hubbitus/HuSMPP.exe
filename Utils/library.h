////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : library.h

#ifndef __LIBRARY_H__
#define __LIBRARY_H__

////////////////////////////////////////////////////////
#include "HuSMPPshared.h"

////////////////////////////////////////////////////////
class CLibrary
{
public:
//
  CLibrary();
  ~CLibrary();

//
  
private:
//
  static void OpenLibrary();
  static void CloseLibrary();

  static void InitializeSockets();
  static void UninitializeSockets();

  static int s_Count;
  static WSADATA m_WSAData;
};

static CLibrary st_DummyLib;

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
