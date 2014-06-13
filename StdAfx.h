// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A4752417_0502_4459_91F8_94D255FC22CB__INCLUDED_)
#define AFX_STDAFX_H__A4752417_0502_4459_91F8_94D255FC22CB__INCLUDED_

//C:\Program Files\Microsoft Visual Studio 8\VC\atlmfc\include\afx.h(24) : fatal error C1189: #error :  Building MFC application with /MD[d] (CRT dll version) requires MFC shared dll version. Please #define _AFXDLL or do not use /MD[d]
// Shit! It is worked on developer mashine, and also has smaller size,
// but just not started (nothing hapen) on server :(
// /MDd switch
//#define _AFXDLL

//+Hu http://lists.boost.org/boost-users/2006/08/21585.php
#define _SCL_SECURE_NO_DEPRECATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WINVER       0x0500
#define WINVER       0x0400
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

//#define  WINVER  0x0400
//#define WINVER 0x0501

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//-77 #include <afxwin.h>         // MFC core and standard components
//-77 #include <afxext.h>         // MFC extensions
//-77 #include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
//-77 #include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdb.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__A4752417_0502_4459_91F8_94D255FC22CB__INCLUDED_)
