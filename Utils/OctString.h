////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : OctString.h


#ifndef __OCTString_H__
#define __OCTString_H__

////////////////////////////////////////////////////////
#include "../HuSMPPshared.h"
//#include "ptrs.h"
//???????????????#include "windef.h"
////////////////////////////////////////////////////////
#include <string>
using namespace std;

////////////////////////////////////////////////////////
class IOctString
{
public:
  //
  virtual
	  void
	  Initialize(
	  const BYTE * data,
	  unsigned int dataSize
	  ) = 0;
  virtual unsigned int GetLength() = 0;
  virtual BYTE* GetData() = 0;

  DECLARE_CH_REFCOUNTING( IOctString )
};

#endif

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////
