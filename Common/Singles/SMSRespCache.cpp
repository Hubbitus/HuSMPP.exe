////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMSRespCache.cpp
// Modifyed by Pavel Alexeev
// Для обмена через виндовые мессаги
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMSRespCache.h"
#include "../../Utils/lock.h"

#include "../../SMS/OutSMS.h"

#include "singleton.h" //Для логов пока

////////////////////////////////////////////////////////

#include <algorithm>

////////////////////////////////////////////////////////
class CSMSRespCacheImpl : public ISMSRespCache{
public:
	CSMSRespCacheImpl();
	virtual ~CSMSRespCacheImpl();

	//Обязательная инициализация начальная
	virtual void Initialize(CWnd * w);
	//Это сброс будет всего, например при ошибке коннекта, или просто реконнекте
	virtual void Initialize();

	virtual void AddSMS( CH<IOutSMS> sms );
	virtual void AddRESP( SP<IPDUSubmitSmResp> resp );
	//Например при принудительном завершении, все надо метить как плохое, поскольку не известно обратного.
	virtual void FlushAllCacheToFailed();

	virtual CH<IOutSMS> GetSendedSMS () /*throw (IOutSMS::Empty)*/;
	virtual CH<IOutSMS> GetFailedSMS () /*throw (IOutSMS::Empty)*/;

	virtual size_t Size();

	virtual void CommitError();
	virtual void UnCommitError();
protected:
	OutSMSlist		m_CachedSMSs;		//Основной контейнер
	OutSMSlist		m_CachedSendedSMSs;	//Успешно отправленные, и на  все части полученные 0 респы
	SequenceList	m_NullResps;		//Номера (Sequence) RESP'ов, которые уже просто не нужны
	RespsList		m_RespWithoutSMS;	//Респы, для которых в КЕШе просто пока нету СМСок (например они выбраны на обработку ошибки)

	CH<IOutSMS>		m_LastFailedSMS;	//Будет тут хранится ДО вызова одного из *CommitError
	bool m_LastFailedSMSactive;			//Действительно ли значение в свойстве выше

private:
	//Окно, которому будем слать сообщения для обработки событий об отправке СМС
  	HWND WM_messageRecipient;
	CWnd * WM_messageRecipientCWND;
	virtual void SendMessageCache (int msg);

	CLock m_Lock;

	//Класс-функция для сравнения и поиска нужной SMS, с добавлением в нее resp'а
	class SMSAddRespCMP {
	friend class ISMSRespCache;
	public:
		SMSAddRespCMP(const CH<IPDUSubmitSmResp> p) : _newResp(p) { }
		bool operator() (CH<IOutSMS> CMPsms) const {
		//SMSка сама ищет, сама добавит в себя, и вернет результат
		return CMPsms->AddRESP(_newResp);
		}
	private:
	const CH<IPDUSubmitSmResp> _newResp;
	};

	//Класс-функция для поиска _неудачно_ отправленной СМСки
	class SMSFailedRespCMP {
	public:
		bool operator() (CH<IOutSMS> CMPsms) const {
		return (CMPsms->getCountFailPDUs() > 0);
		}
	};

	//Сравнение SP<IPDUSubmitSmResp> по его SequenseNumber
	class CMPRespBySeqN {
	public:
		CMPRespBySeqN (DWORD cmp) : _cmp(cmp){};
		bool operator() (CH<IPDUSubmitSmResp> & CMPresp) const {
		return (CMPresp->GetSequenceNumber() == _cmp);
		}
	private:
		DWORD _cmp;
	};
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMSRespCache, CSMSRespCacheImpl )

////////////////////////////////////////////////////////
CSMSRespCacheImpl::CSMSRespCacheImpl() : WM_messageRecipient (0), m_LastFailedSMSactive (false)
{
}

////////////////////////////////////////////////////////
CSMSRespCacheImpl::~CSMSRespCacheImpl()
{
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::Initialize(){
CLocalLock lock( m_Lock );

//Организовать какое-то действие, по коммиту того что осталось
FlushAllCacheToFailed();
Sleep(2000);//чтобы была возможность обработать. проверять не будем, очистим.

m_CachedSMSs.clear();
m_CachedSendedSMSs.clear();
m_NullResps.clear();
m_RespWithoutSMS.clear();

m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::Initialize(CWnd * w){
CLocalLock lock( m_Lock );
WM_messageRecipientCWND = w;
//Дальше как простая очистка
Initialize();
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::FlushAllCacheToFailed(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::FlushAllCacheToFailed()");
//Все оставшиеся помечаем ошибочными
OutSMSlist::iterator allI = m_CachedSMSs.begin();

	while (allI != m_CachedSMSs.end()){
	(*allI)->MarkBad (ESME_FLUSHERR);//ESME_FLUSHERR правда и так поумолчанию
	}

//И шлем стандартное сообщение на их обработку
SendMessageCache(WM_SMPP_SUBMIT_RESP_FAILED);
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::AddSMS( CH<IOutSMS> sms ){
CLocalLock lock( m_Lock );

m_CachedSMSs.push_back(sms);
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::AddRESP( SP<IPDUSubmitSmResp> respSP ){
CLocalLock lock( m_Lock );

//-70 Придется так делать, опять через Буфер, раз не удается никак передать CH<>...
CH<IPDUSubmitSmResp> resp; resp->Initialize(respSP->GetRawData(), respSP->GetInSocket());

OutSMSlist::iterator fi = std::find_if(m_CachedSMSs.begin(), m_CachedSMSs.end(), SMSAddRespCMP(resp));

	if (fi != m_CachedSMSs.end()){//Значит найдено, и сопоставлено
	//Проверяем тогда не был ли ответ последним, и нельзя ли судить об успешности СМС
		if ( (*fi)->getCountFailPDUs() == 0 ){//Респ Ок
			//Успешная отправка полной СМС
			if ( ((*fi)->RespComplete()) && ((*fi)->getCountOkPDUs() == (*fi)->getCountPDUs() )) {
			//Успешная! Перемещаем, чтобы в следующий раз в ней больше не искалось!
			m_CachedSendedSMSs.splice(m_CachedSendedSMSs.end(),m_CachedSMSs, fi); 
			//Ну и надо отправить сообщение тому кто будет этот случай обрабатывать:
			SendMessageCache(WM_SMPP_SUBMIT_RESP_SENDED);
			}			
		}
		else{//Ошибка
		SendMessageCache(WM_SMPP_SUBMIT_RESP_FAILED);
		}		
	}
	else{//НЕ найдено.
	//Тогда ищем, может быть этот resp вообще не нужен
	SequenceList::iterator si = std::find(m_NullResps.begin(), m_NullResps.end(), resp->GetSequenceNumber() );
		if (si != m_NullResps.end()){//Не нужен
		m_NullResps.erase(si);
		}
		else{//Тогда скорее всего это СМСкак была выбрана как ошибочная, записываем, в НЕимеющие сопоставленных SMS
		m_RespWithoutSMS.push_back(resp);
		}
	}
}

////////////////////////////////////////////////////////
void
CSMSRespCacheImpl::SendMessageCache (int msg){
CLocalLock lock( m_Lock );
//-87
	if (!WM_messageRecipient) WM_messageRecipient = WM_messageRecipientCWND->GetSafeHwnd();
//-87
	::PostMessage( WM_messageRecipient, WM_COMMAND, msg, 0);
}

////////////////////////////////////////////////////////
//По одной выдаем, с УДАЛЕНИЕМ, конец - throw new IOutSMS::Empty
CH<IOutSMS>
CSMSRespCacheImpl::GetSendedSMS (){
CLocalLock lock( m_Lock );

	if (!m_CachedSendedSMSs.empty()){
	CH<IOutSMS> retVal = m_CachedSendedSMSs.front();
	m_CachedSendedSMSs.pop_front();
	return retVal;
	}
	else throw new IOutSMS::Empty;
}

////////////////////////////////////////////////////////
//По одной выдаем, с УДАЛЕНИЕМ, конец - throw new IOutSMS::Empty
CH<IOutSMS>
CSMSRespCacheImpl::GetFailedSMS (){
CLocalLock lock( m_Lock );

//Должно быть вызвано *CommitError так или иначе ДО следующего вызова
chASSERT ( !m_LastFailedSMSactive );

//ISMSRespCache::
OutSMSlist::iterator fs = std::find_if(m_CachedSMSs.begin(), m_CachedSMSs.end(), SMSFailedRespCMP());
	
	if (fs != m_CachedSMSs.end()){//Значит найдено, и сопоставлено
	m_LastFailedSMS = *fs;
	m_CachedSMSs.erase(fs);
	m_LastFailedSMSactive = true;
	return m_LastFailedSMS;
	}
	else throw new IOutSMS::Empty;//Не найдено больше
}

////////////////////////////////////////////////////////
//Подтвердить ошибку, все, больше не надо обрабатывать части этой СМС
void
CSMSRespCacheImpl::CommitError(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::CommitError()");

//Должен быть!
chASSERT ( m_LastFailedSMSactive );

/*Подтвердили, значит все уже полученные респы удаляем из m_RespWithoutSMS
и оставшиеся (Которых не было в m_RespWithoutSMS) поместить в m_NullResps
*/
//пойдем по всем ПДУ, у которых НЕТу респов, только на них могли поступить они позже
IOutSMS::SMSPairVector::iterator pairI = m_LastFailedSMS->GetPDUs().begin();
	while (pairI != m_LastFailedSMS->GetPDUs().end()){
		if (pairI->second->GetSequenceNumber() == NOT_RESP_SEQ){//Значит респ НЕ был получен
		//значит _мог быть_ получен позже, пытаемся удалить
		RespsList::iterator withoutIter = std::find_if(m_RespWithoutSMS.begin(), m_RespWithoutSMS.end(), CMPRespBySeqN(pairI->second->GetSequenceNumber()));
			if (withoutIter != m_RespWithoutSMS.end()){//Значит найден
			m_RespWithoutSMS.erase(withoutIter);
			}
			else{//Значит НЕ найден, добавляем в НЕнужные
			m_NullResps.push_back(pairI->second->GetSequenceNumber());
			}
		}
	++pairI;
	}

m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
//НЕ подтвердить, ВЕРНУТЬ ее на обработку и ожидание РЕСПов. Возможно что она уже изменена. Например перепосланы некоторые части снова.
void
CSMSRespCacheImpl::UnCommitError(){
CLocalLock lock( m_Lock );

GETLOG->AddToLog("CSMSRespCacheImpl::UnCommitError()");

chASSERT ( m_LastFailedSMSactive );
/*НЕ подтвердили, значит вернуть (возможно измененную, она по ссылке передавалась) СМСку
в кеш ожидания РЕСПов общий, посмотрев, не пришло ли за это время в нее каких-то РЕСПов в m_RespWithoutSMS
*/

//пойдем по всем ПДУ, у которых НЕТу респов, только на них могли поступить они позже
IOutSMS::SMSPairVector::iterator pairI = m_LastFailedSMS->GetPDUs().begin();
	while (pairI != m_LastFailedSMS->GetPDUs().end()){
		if (pairI->second->GetSequenceNumber() == NOT_RESP_SEQ){//Значит респ НЕ был получен
		//значит _мог быть_ получен позже, пытаемся переместить
		RespsList::iterator withoutIter = std::find_if(m_RespWithoutSMS.begin(), m_RespWithoutSMS.end(), CMPRespBySeqN(pairI->second->GetSequenceNumber()));
			if (withoutIter != m_RespWithoutSMS.end()){//Значит найден
			m_LastFailedSMS->AddRESP(*withoutIter);
			m_RespWithoutSMS.erase(withoutIter);
			}
//лучше пустьпо старому пока выше останется, потому что там через метод, с посылкой сообщений...
//		m_CachedSendedSMSs.splice(m_CachedSendedSMSs.end(),m_CachedSMSs, fi); 
		}
	++pairI;
	}

//AddSMS(m_LastFailedSMS); нельзя, уже заблокировано
//Ну и обратно его в ожидание
m_CachedSMSs.push_back(m_LastFailedSMS);
m_LastFailedSMSactive = false;
}

////////////////////////////////////////////////////////
size_t
CSMSRespCacheImpl::Size(){
return m_CachedSMSs.size();
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////