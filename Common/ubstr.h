#pragma once

#ifndef __UBSTR_H__
#define __UBSTR_H__
#include <limits.h>

#pragma warning( push )
#pragma warning(disable:4800)

inline bool
ustrncpy( char* p1, const wchar_t* p2, size_t c )
{
  size_t cb = wcstombs(p1, p2, c);
  return cb != c && cb != (size_t) -1;
}
#pragma warning( pop )


inline bool
ustrncpy(wchar_t* p1, const wchar_t* p2, size_t c)
{
  size_t index = c;
  wcsncpy(p1, p2, index);
  return p1[c-1] == 0;
}

inline bool
ustrncpy(char* p1, const char* p2, size_t c)
{
  strncpy(p1, p2, c);
  return p1[c-1] == 0;
}

inline bool
ustrncpy(wchar_t* p1, const char* p2, size_t c)
{
  size_t cb = mbstowcs(p1, p2, c);
  return cb != c && cb != (size_t) -1;
}

class _UNCC
{
public:
  _UNCC(const char* psz)
  {
    size_t c;
    c = strlen(psz)+1;
    m_cStr = new char[c];
    m_wStr = new wchar_t[c];

    ustrncpy(m_cStr, psz, c);
    ustrncpy(m_wStr, psz, c);
  }

  _UNCC(const wchar_t* pwsz)
  {
    size_t c;
    c = wcslen(pwsz)+1;
    m_cStr = new char[c];
    m_wStr = new wchar_t[c];

    ustrncpy(m_cStr, pwsz, c);
    ustrncpy(m_wStr, pwsz, c);
  }


  virtual ~_UNCC()
  {
    delete[] m_cStr;
    delete[] m_wStr;
    m_cStr = 0;
    m_wStr = 0;
  }

  operator char*()
  {
    return m_cStr;
  }

  operator wchar_t*()
  {
    return m_wStr;
  }

protected:
private:
  char* m_cStr;
  wchar_t* m_wStr;
};



class _UBSTR
{
public:
  _UBSTR(const char* psz):
    m_bstr(SysAllocStringLen(0, (UINT)strlen(psz)))
  {
      ustrncpy(m_bstr, psz, INT_MAX);
  }
  _UBSTR(const wchar_t* pwsz):
    m_bstr(SysAllocString(pwsz))
  {
  }
  virtual ~_UBSTR()
  {
    SysFreeString(m_bstr);
  }

  operator BSTR() const
  {
    return m_bstr;
  }
private:
  BSTR m_bstr;

};

////////////////////////////////////////
inline OLECHAR* SAFEBSTR( BSTR b )
{
  return b ? b : OLESTR("");
}

////////////////////////////////////////
inline const wchar_t* SAFEWCHAR( const wchar_t* b )
{
  return b ? b : OLESTR("");
}

////////////////////////////////////////////////////////
inline const char*
SAFESTR( const char* str )
{
  return ( str ? str : "" );
}

#endif
