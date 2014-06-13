////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : OctString.cpp

////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../Common/CmnHdr.h"

#include "OctString.h"
#include "../stdafx.h"
////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////

class COctStringImpl : public IOctString
{
public:
  //
  COctStringImpl();
  virtual ~COctStringImpl();

  //
  virtual void Initialize( const BYTE* data, unsigned int dataSize );
  virtual unsigned int GetLength();
  virtual BYTE* GetData();

protected:
private:
  // private methods
  void Cleanup();

  // private fields
  BYTE* m_Data;
  unsigned int m_DataSize;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( IOctString, COctStringImpl )

////////////////////////////////////////////////////////
COctStringImpl::COctStringImpl() : m_Data( NULL ), m_DataSize( 0 ) 
{
}

////////////////////////////////////////////////////////
COctStringImpl::~COctStringImpl() 
{ 
  Cleanup();
}

////////////////////////////////////////////////////////
void
COctStringImpl::Initialize( const BYTE* data, unsigned int dataSize )
{
  Cleanup();
  m_DataSize = dataSize;

  if ( m_DataSize )
  {
    m_Data = new BYTE[ m_DataSize + 1 ];
    memcpy( m_Data, data, m_DataSize );
    m_Data[ m_DataSize ] = 0;
  }
}

////////////////////////////////////////////////////////
unsigned int
COctStringImpl::GetLength()
{ 
  return m_DataSize;
}

////////////////////////////////////////////////////////
BYTE*
COctStringImpl::GetData()
{
  return m_Data;
}

////////////////////////////////////////////////////////
void
COctStringImpl::Cleanup()
{
  if ( m_Data )
  {
    delete[] m_Data;
    m_Data = NULL;
    m_DataSize = 0;
  }
}

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////