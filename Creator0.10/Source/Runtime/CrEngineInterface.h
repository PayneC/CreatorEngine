/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINEINTERFACE_H
#define _CREATOR_ENGINEINTERFACE_H

#include "CrEngine.h"
#include "Lua\CrLuaState.h"

namespace CreatorEngine
{
	int Initialization();
	int Start(CrScene * pScene);
	void Stop();
}

#endif