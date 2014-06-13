////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : PDUHeader.h

#ifndef __PDUHEADER_H__
#define __PDUHEADER_H__

////////////////////////////////////////////////////////
//-1#include "SMPPHeader.h"
//#include "PDU.h"
#include "../HuSMPPshared.h"

///////////Temp
//#include "../Utils/ptrs.h"
#include <Winsock2.h>
////////////////////////////////////////////////////////
#pragma pack(push, 1)

////////////////////////////////////////////////////////
typedef struct PDUHeader
{
  PDUHeader()
  {
    command_length = 0;
    command_id = 0;
    command_status = 0;
    sequence_number = 0;
  }

  void HTON()
  {
    command_length = htonl( command_length );
    command_id = htonl( command_id );
    command_status = htonl( command_status );
    sequence_number = htonl( sequence_number );
  }

  void NTOH()
  {
    command_length = ntohl( command_length );
    command_id = ntohl( command_id );
    command_status = ntohl( command_status );
    sequence_number = ntohl( sequence_number );
  }


  DWORD command_length;
  DWORD command_id;
  DWORD command_status;
  DWORD sequence_number;

} PDUHeader;

////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
// =================== END OF FILE =====================
////////////////////////////////////////////////////////
