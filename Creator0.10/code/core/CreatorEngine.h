/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_CREATORENGINE_H
#define _CREATOR_CREATORENGINE_H

#include "CrEngine.h"
#include "Lua\CrLuaState.h"

namespace CreatorEngine
{
	int Initialization();
	int Start(CrScene * pScene);
	void Stop();

	void RegisterLuaAPI(lua_State * _L);
}

#endif