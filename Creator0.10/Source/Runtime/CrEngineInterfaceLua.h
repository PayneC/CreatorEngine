/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINEINTERFACE_LUA_H
#define _CREATOR_ENGINEINTERFACE_LUA_H

#include "CrEngine.h"
#include "CrLuaState.h"

namespace CreatorEngineLua
{
	void RegisterLuaAPI(lua_State * _L);

	int Stop(lua_State * L);
}

#endif