////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : library.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"
#include "library.h"
#include "Common/Singles/singleton.h"

/*-52
#include "CmnHdr.h"

#include "library.h"
#include "Common/Singles/singleton.h"
*/

////////////////////////////////////////////////////////
int CLibrary::s_Count = 0;
WSADATA CLibrary::m_WSAData;

////////////////////////////////////////////////////////
inline CLibrary::CLibrary()
{
  if ( s_Count++ == 0 )
    OpenLibrary();
}

////////////////////////////////////////////////////////
inline CLibrary::~CLibrary()
{
  if ( --s_Count == 0 )
    CloseLibrary();
}

////////////////////////////////////////////////////////
void 
CLibrary::OpenLibrary()
{
  CSingleton::Make();
  InitializeSockets();
}

////////////////////////////////////////////////////////
void 
CLibrary::CloseLibrary()
{
  CSingleton::Destroy();
  UninitializeSockets();
}

////////////////////////////////////////////////////////
void
CLibrary::InitializeSockets()
{
  WORD version = MAKEWORD( 2,0 );
  if ( WSAStartup(version, &m_WSAData ) != 0 )
    throw CError( "CLibrary::InitializeSockets() - Error in winsocket initalization" );
 
  if ( LOBYTE( m_WSAData.wVersion ) < 2 )
    throw CError( "CLibrary::InitializeSockets() - Wrong winsocket version" );
}

////////////////////////////////////////////////////////
void
CLibrary::UninitializeSockets()
{
  WSACleanup();
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////
