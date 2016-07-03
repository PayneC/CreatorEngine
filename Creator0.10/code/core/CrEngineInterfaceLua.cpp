#include "CreatorEngine.h"

using namespace CreatorEngine;

int LStop(lua_State * L)
{
	Stop();

	lua_pushnumber(L, 0);

	return 1;
}

int LInitialization(lua_State * L)
{
	int rlt = Initialization();

	lua_pushnumber(L, rlt);

	return 1;
}

void CreatorEngine::RegisterLuaAPI(lua_State * _L)
{
	LuaAPI_Register(_L, LStop);
	LuaAPI_Register(_L, LInitialization);
}