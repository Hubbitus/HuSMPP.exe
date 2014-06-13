////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : sequencer.h

#ifndef __SEQUENCER_H__
#define __SEQUENCER_H__

////////////////////////////////////////////////////////
//-1#include "SMPPHeader.h"
#include "../HuSMPPshared.h"
////////////////////////////////////////////////////////
class CSequencer
{
public:
  CSequencer() : m_Value( 1 ) {}
  ~CSequencer(){}

  operator DWORD() { return m_Value++; }
  
protected:
private:
  DWORD m_Value;

};

#endif

// =================== END OF THE FILE =================
////////////////////////////////////////////////////////
