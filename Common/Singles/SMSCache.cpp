////////////////////////////////////////////////////////
// Project : HuSMPPClient
// Module  : SMSCache.cpp
// Author  : Pavel Alexeev (Pahan-Hubbitus)
//		Rewritten 2008-05-19
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMSCache.h"
#include "../../Utils/lock.h"

////////////////////////////////////////////////////////
// CSMSCacheImpl class
class CSMSCacheImpl : public ISMSCache{
public:

	CSMSCacheImpl();
	virtual ~CSMSCacheImpl();

	virtual void Initialize();

	//-61
	virtual void AddPDU( CH<IPDUCache> pdu );
	virtual void AddPDU( CH<IPDU> pdu );
	virtual CH<IPDUIterator> GetAllCachedPDUs();
  
protected:

private:
	CLock m_Lock;
	CH<IPDUIterator> m_CachedPDUs;
};

////////////////////////////////////////////////////////
IMPLEMENT_CH_REFCOUNTING( ISMSCache, CSMSCacheImpl )

////////////////////////////////////////////////////////
CSMSCacheImpl::CSMSCacheImpl()
{
}

////////////////////////////////////////////////////////
CSMSCacheImpl::~CSMSCacheImpl()
{
}

////////////////////////////////////////////////////////
void
CSMSCacheImpl::Initialize()
{
}

////////////////////////////////////////////////////////
//-61
void
CSMSCacheImpl::AddPDU( CH<IPDUCache> pdu ){
CLocalLock lock( m_Lock );

m_CachedPDUs->PutPDU( SafeCastCH<IPDU, IPDUCache>( pdu ) );
}

////////////////////////////////////////////////////////
//-61
void
CSMSCacheImpl::AddPDU( CH<IPDU> pdu ){
CLocalLock lock( m_Lock );

m_CachedPDUs->PutPDU( pdu );
}
////////////////////////////////////////////////////////
CH<IPDUIterator>
CSMSCacheImpl::GetAllCachedPDUs(){
CLocalLock lock( m_Lock );

CH<IPDUIterator> retVal = m_CachedPDUs;
CH<IPDUIterator> newCacheVal;
m_CachedPDUs = newCacheVal;

return retVal;
}

// =================== END OF FILE =====================
////////////////////////////////////////////////////////