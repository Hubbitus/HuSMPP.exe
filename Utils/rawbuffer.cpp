////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : rawbuffer.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../HuSMPPshared.h"
#include "rawbuffer.h"
//-15#include "../stdafx.h"
////////////////////////////////////////////////////////
// CRORawBufferImpl class
////////////////////////////////////////////////////////

class CRawBufferImpl : public IRawBuffer
{
public:
  //
  CRawBufferImpl();
  virtual ~CRawBufferImpl();

  virtual unsigned int GetAvailableDataSize();
  virtual const BYTE* PeekData();
  virtual void Skip( int bytes );

  virtual void AddData( const BYTE* buffer, int bufferLength );
  virtual void Clear();
  virtual CH<IRORawBuffer> ROSubBuffer();
  virtual CH<IRawBuffer> Clone();
  
  virtual string GetCString( unsigned int maxSize );
  //-46 My см описание в .h-файле
  virtual string GetString( WORD Size );
  virtual BYTE GetBYTE();
  virtual WORD GetWORD();
  virtual DWORD GetDWORD();

  virtual CH<IOctString> GetOctString();

protected:

private:
// private methods
  BYTE* m_RawData;

  DWORD m_SizeAllocated;
  DWORD m_SizeUsed;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IRORawBuffer, CRawBufferImpl )
IMPLEMENT_CH_REFCOUNTING( IRawBuffer, CRawBufferImpl )

////////////////////////////////////////////////////////
CRawBufferImpl::CRawBufferImpl()
{
  m_RawData = NULL;
  m_SizeAllocated = 0;
  m_SizeUsed = 0;
}

////////////////////////////////////////////////////////
CRawBufferImpl::~CRawBufferImpl()
{
  if ( m_RawData )
  {
    free( m_RawData );
    m_RawData = NULL;
  }
}

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
void 
CRawBufferImpl::AddData( const BYTE* buffer, int bufferLength )
{
  BYTE* newMem;
  newMem = ( BYTE* ) realloc( m_RawData, m_SizeAllocated + bufferLength );
  if ( !newMem )
    throw CError(" CRawBufferImpl::AddData() - Can't allocate memory ");

  m_RawData = newMem;

  memcpy( m_RawData + m_SizeAllocated, buffer, bufferLength );
  m_SizeAllocated += bufferLength;
}

////////////////////////////////////////////////////////
unsigned int 
CRawBufferImpl::GetAvailableDataSize()
{
  int retVal;
  retVal = m_SizeAllocated - m_SizeUsed;

  if ( retVal < 0 )
    retVal = 0;

  return ( unsigned int )retVal;
}

////////////////////////////////////////////////////////
const BYTE* 
CRawBufferImpl::PeekData()
{
  BYTE* retVal = m_RawData + m_SizeUsed;
  return retVal;
}

////////////////////////////////////////////////////////
void 
CRawBufferImpl::Skip( int bytes )
{
  if ( bytes < 0 )
    bytes = 0;

  if ( m_SizeAllocated < ( unsigned int ) bytes )
    bytes = m_SizeAllocated;
  
  int newSize = m_SizeAllocated - bytes;

  BYTE* newMem;
  newMem = ( BYTE* ) malloc( newSize );
  if ( !newMem )
    throw CError(" CRawBufferImpl::Skip() - Can't allocate memory ");

  memcpy( newMem, m_RawData + bytes, newSize );
  free( m_RawData );
  m_RawData = newMem;
  
  m_SizeAllocated = newSize;
  m_SizeUsed = 0;
}

////////////////////////////////////////////////////////
void 
CRawBufferImpl::Clear()
{
  if ( m_RawData )
  {
    free( m_RawData );
    m_RawData = NULL;
  }

  m_SizeAllocated = 0;
  m_SizeUsed = 0;
}

////////////////////////////////////////////////////////
CH<IRORawBuffer>
CRawBufferImpl::ROSubBuffer()
{
  CH<IRawBuffer> retVal;
  retVal->AddData( PeekData(), GetAvailableDataSize() );

  return SafeCastCH<IRORawBuffer, IRawBuffer>( retVal );
}

////////////////////////////////////////////////////////
CH<IRawBuffer>
CRawBufferImpl::Clone()
{
  CH<IRawBuffer> retVal;
  retVal->AddData( PeekData(), GetAvailableDataSize() );
  return retVal;
}

////////////////////////////////////////////////////////
string 
CRawBufferImpl::GetCString( unsigned int maxSize )
{
  string retVal = "";

  unsigned int avData = GetAvailableDataSize();
  unsigned int bufSize = ( avData > maxSize ) ? maxSize : avData;

  if ( bufSize > 0 )
  {
    char* allData = ( char* ) PeekData();

    char* buf = new char[ bufSize ];

    for ( unsigned int i = 0; i < bufSize; i++ )
    {
      buf[ i ] = allData[ i ];
      if ( buf[ i ] == 0 )
        break;
    }

    buf[ bufSize - 1 ] = 0;
    retVal = buf;
    delete[] buf;

    Skip( ( int ) retVal.length() + 1 );
  }
  
  return retVal;
}

////////////////////////////////////////////////////////
//+My смотри описание в rawbuffer.h
//-46
std::string 
CRawBufferImpl::GetString( WORD Size ){
std::string retVal = "";
unsigned int avData = GetAvailableDataSize();
unsigned int bufSize = ( avData > Size ) ? Size : avData;

	if ( bufSize > 0 ){
	retVal = std::string ( ( char* ) PeekData(), bufSize );
    Skip( ( int ) bufSize );
	}
  
return retVal;
}

////////////////////////////////////////////////////////
BYTE
CRawBufferImpl::GetBYTE()
{
  BYTE retVal = 0;
  unsigned int avData = GetAvailableDataSize();

  if ( avData >= sizeof( BYTE ) )
  {
    retVal = *( ( BYTE* ) PeekData() );
    Skip( sizeof( retVal ) );
  }

  return retVal;
}

////////////////////////////////////////////////////////
WORD
CRawBufferImpl::GetWORD()
{
  WORD retVal = 0;
  unsigned int avData = GetAvailableDataSize();

  if ( avData >= sizeof( WORD ) )
  {
    retVal = *( ( WORD* ) PeekData() );
    Skip( sizeof( retVal ) );
  }

  return retVal;
}

////////////////////////////////////////////////////////
DWORD
CRawBufferImpl::GetDWORD()
{
  DWORD retVal = 0;
  unsigned int avData = GetAvailableDataSize();

  if ( avData >= sizeof( DWORD ) )
  {
    retVal = *( ( DWORD* ) PeekData() );
    Skip( sizeof( retVal ) );
  }

  return retVal;
}

////////////////////////////////////////////////////////
CH<IOctString>
CRawBufferImpl::GetOctString()
{
  CH<IOctString> retVal;

  unsigned int avData = GetAvailableDataSize();
  if ( avData > 0 )
  {
    BYTE len = GetBYTE();
    avData = GetAvailableDataSize();

    BYTE bufSize = ( BYTE )( ( avData > len ) ? len : avData );
    retVal->Initialize( PeekData(), bufSize );
    Skip( bufSize );
  }

  return retVal;
}

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////