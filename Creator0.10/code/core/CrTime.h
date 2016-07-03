/*
CreatorEngine
Class CrTime
Payne
*/

#ifndef _CREATOR_TIME_H
#define _CREATOR_TIME_H

#include "CrDefine.h"
#include <CrSingleton.h>

class CrTime : public CrSingleton<CrTime>
{
public:
	CrTime();
	~CrTime();
	
	float GetCurrentTime();
	float GetDelateTime();
	EasyGet(double, m_lfCurrentTime, CurrentTimeLF);
	EasyGet(double, m_lfStartTime, StartTime);
	EasyGet(double, m_lfDelateTime, DelateTimeLF);
	EasyGet(double, m_lfBeforeTime, BeforeTime);
	EasyGet(double, m_lfFrameInterval, FrameInterval);
	EasyGet(unsigned int, m_uFramesPerSecond, FramesPerSecond);

	void SetFrameInterval(double frameInterval);
	void SetFramesPerSecond(unsigned int FPS);

	bool Init();
	void Update();
	bool IsMeetInterval();
private:

};

#endif