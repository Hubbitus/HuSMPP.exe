////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : rawbuffer.h

#ifndef __RAWBUFFER_H__
#define __RAWBUFFER_H__

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"

#include "OctString.h"
////////////////////////////////////////////////////////
#include <string>
using namespace std;

////////////////////////////////////////////////////////
class IRORawBuffer
{
public:
  virtual unsigned int GetAvailableDataSize() = 0;
  virtual const BYTE* PeekData() = 0;
  virtual void Skip( int bytes ) = 0;

  virtual std::string GetCString( unsigned int maxSize ) = 0;
  //+Hu В отличие от GetCString НЕ заполняет последний символ 0
  //В отличие от GetOctString НЕ читает длину из буфера, а берет из параметра
  //необходима в случае, когда длина берется подругому, а не как в GetOctString GetBYTE!
  virtual std::string GetString( WORD Size ) = 0;
  virtual BYTE GetBYTE() = 0;
  virtual WORD GetWORD() = 0;
  virtual DWORD GetDWORD() = 0;

  virtual CH<IOctString> GetOctString() = 0;

  DECLARE_CH_REFCOUNTING( IRORawBuffer )
};

////////////////////////////////////////////////////////
class IRawBuffer : public IRORawBuffer
{
public:
  virtual void AddData( const BYTE* buffer, int bufferLength ) = 0;
  virtual void Clear() = 0;

  virtual CH<IRORawBuffer> ROSubBuffer() = 0;
  virtual CH<IRawBuffer> Clone() = 0;

  DECLARE_CH_REFCOUNTING( IRawBuffer )
};

#endif

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////
