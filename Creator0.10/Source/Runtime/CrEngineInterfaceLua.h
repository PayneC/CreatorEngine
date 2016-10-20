/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINEINTERFACE_LUA_H
#define _CREATOR_ENGINEINTERFACE_LUA_H

#include "CrEngine.h"
#include "Lua\CrLuaState.h"

namespace CreatorEngineLua
{
	void RegisterLuaAPI(lua_State * _L);

	int Stop(lua_State * L);
	int Initialization(lua_State * L);
}

#endif