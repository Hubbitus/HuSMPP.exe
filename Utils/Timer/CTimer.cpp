////////////////////////////////////////////////////////
// Project	: HuSMPPClient
// Module	: CTimer.cpp
// Author	: Pavel Alexeev (Pahan-Hubbitus)
//
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CTimer.h"

////////////////////////////////////////////////////////

//ПЛОХО, указатель один на 1 объект. Но пока их поидее больше и не должно быть
CTimer* curTimerClass;

////////////////////////////////////////////////////////
//Функция-обертка, для получения события таймера. Метод сразу нельзя вызвать, если это не окно!!
void CALLBACK EXPORT
HuTimerProc(HWND hwnd, UINT msg, UINT nIDEvent, DWORD dwTime){
//MessageBeep(0xFFFFFFFF);   // Beep
::curTimerClass->OnTimer( nIDEvent );
}

////////////////////////////////////////////////////////
CTimer::CTimer(void)
{
}

////////////////////////////////////////////////////////
CTimer::~CTimer(void)
{
}

////////////////////////////////////////////////////////
STimer const &
CTimer::StartTimer(UINT_PTR nIDEvent, UINT nElapse, char * name = ""){
curTimerClass = this;

STimer tmpTimer;
//	tmpTimer.link = this;//Пока всегда :)
tmpTimer.m_nIDEvent = nIDEvent;
tmpTimer.m_nElapse = nElapse;
tmpTimer.m_nTimer = ::SetTimer(0, tmpTimer.m_nIDEvent, tmpTimer.m_nElapse, HuTimerProc);
tmpTimer.name = name;

	//Вставляем!
TimerS[tmpTimer.m_nTimer] = tmpTimer;
return STimerByMTimer(tmpTimer.m_nTimer);//Не обязательно
}

////////////////////////////////////////////////////////
UINT_PTR
CTimer::StartTimer(STimer & timer){
return ::SetTimer(0, timer.m_nIDEvent, timer.m_nElapse, HuTimerProc);
}

////////////////////////////////////////////////////////
void
CTimer::KillTimer(STimer & timer, bool remove = true){
	::KillTimer(0, timer.m_nTimer);
	if (remove) TimerS.erase(timer.m_nTimer);
}

////////////////////////////////////////////////////////
void
CTimer::RestartTimer(UINT_PTR nIDEvent){
	try{
	STimer tmpTmr = STimerByIDEvent (nIDEvent);
	RestartTimer(tmpTmr);
	}
	catch(STimer_Bad_Timer * STbad){
	delete STbad;
	}
}

////////////////////////////////////////////////////////
void
CTimer::RestartTimer(STimer & timer){
	try{
	//Restart onli if it was. If KillTimer throws error - so, start not needed!
	KillTimer(timer, false);
	StartTimer(timer);
	}
	catch(STimer_Bad_Timer * STbad){
	delete STbad;
	}
}

////////////////////////////////////////////////////////
STimer const &
CTimer::STimerByMTimer	(UINT_PTR nTimer) const{
	TimersMap::const_iterator tmrIter = TimerS.find ( nTimer );
	if ( tmrIter != TimerS.end() )
	return tmrIter->second;
	else throw new STimer_Bad_Timer;
//	else return 0;//Пока не придумал лучше
}

////////////////////////////////////////////////////////
STimer const &
CTimer::STimerByIDEvent (UINT_PTR nIDEvent) const{
TimersMap::const_iterator tmrIter = TimerS.begin();
	while ( (tmrIter != TimerS.end()) && ( tmrIter->second.m_nIDEvent != nIDEvent) ){
	tmrIter++;
	}

	if ( tmrIter != TimerS.end() )
	return tmrIter->second;
	else throw new STimer_Bad_Timer;
//	else return 0;//Пока не придумал лучше
}