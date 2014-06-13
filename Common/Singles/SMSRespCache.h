////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMSRespCache.h
// Modifyed by Pavel Alexeev
// Для обмена через виндовые мессаги
//
//	2008-09-18
//	- Added method Size()
////////////////////////////////////////////////////////

#ifndef __SMSRespCache_H__
#define __SMSRespCache_H__

////////////////////////////////////////////////////////
#include "../../HuSMPPshared.h"

#include "../../SMPP/PDU/PDUSubmitSmResp.h"

#include <list>
////////////////////////////////////////////////////////
class ISMSRespCache{
public:
	typedef list<CH<IOutSMS>> OutSMSlist;
	typedef list<DWORD> SequenceList;
	typedef list<CH<IPDUSubmitSmResp>> RespsList;
	virtual void Initialize(CWnd * w) = 0;

	virtual void AddSMS( CH<IOutSMS> sms ) = 0;
	virtual void AddRESP( SP<IPDUSubmitSmResp> resp ) = 0;
	//Например при принудительном завершении, все надо метить как плохое, поскольку не известно обратного.
	virtual void FlushAllCacheToFailed() =0;

	virtual CH<IOutSMS> GetSendedSMS () =0;
	//Вовне, после вызова GetFailedSMS, НЕОБХОДИМО вызвать одну из следующих функций CommitError или UnCommitError
	virtual CH<IOutSMS> GetFailedSMS () =0;

	//Amount of cached *NON-COMPLEATED* (where not all Resps got) SMS
	virtual size_t Size() =0;

	virtual void CommitError() =0;//Подтвердить ошибку, все, больше не надо обрабатывать части этой СМС
	virtual void UnCommitError() =0;//НЕ подтвердить, ВЕРНУТЬ ее на обработку и ожидание РЕСПов. Возможно что она уже изменена. Например перепосланы некоторые части снова.
protected:
	virtual void SendMessageCache (int msg) =0;

DECLARE_CH_REFCOUNTING( ISMSRespCache )
};

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////