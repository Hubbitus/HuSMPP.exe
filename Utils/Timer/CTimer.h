////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: CTimer.h
// Author	: Pavel Alexeev (Pahan-Hubbitus)
//
//	2008-09-18
//	- Methods ResetTimer renamed to RestartTimer.
////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////

#include <map>

////////////////////////////////////////////////////////

struct STimer_Bad_Timer{};

////////////////////////////////////////////////////////

struct STimer {
	STimer(){};
UINT_PTR m_nIDEvent;//Номер который передается в StartTimer
UINT_PTR m_nTimer;	//Номер который возвращается, и по которому его потом идентифицируем
UINT m_nElapse;		//Время в ms
char * name;		//Просто какое-то имя, не обязательно
//CTimer * link;		//Указатель, кого вызывать метод OnTimer (m_Timer)
};

typedef std::map<UINT_PTR, STimer> TimersMap;
//<[m_nTimer], STimer>

class CTimer{
private:
	TimersMap TimerS;

public:
	CTimer(void);
	~CTimer(void);

STimer const & /* m_nTimer */ StartTimer(UINT_PTR nIDEvent, UINT nElapse, char * name);
private:
	UINT_PTR /* m_nTimer */ StartTimer(STimer & timer);

public:
void KillTimer(STimer & timer, bool remove /*= true*/);
void RestartTimer(UINT_PTR nIDEvent);
void RestartTimer(STimer & timer);

STimer const & STimerByIDEvent	(UINT_PTR nIDEvent) const /* throw (Bad_Timer) */;
STimer const & STimerByMTimer	(UINT_PTR m_nTimer) const /* throw (Bad_Timer) */;

////TIMER
//void CALLBACK EXPORT OnTimer(HWND hwnd, UINT msg, UINT idTimer, DWORD dwTime);
virtual void OnTimer( UINT nIDEvent ) = 0;

};
