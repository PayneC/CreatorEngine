/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINE_H
#define _CREATOR_ENGINE_H

#include <Core.h>

static class DLL_ClASS CrEngine
{
public:
	static int Initialization();
	static int Start();
	static void Stop();
	static bool Init();
	static void Destory();
	static void OnEnter();
	static int MainLoop();
	static void OnExit();

private:
	static bool m_isRun;
	static bool m_isInit;
	static double m_lfTotalDelay;
};
#endif