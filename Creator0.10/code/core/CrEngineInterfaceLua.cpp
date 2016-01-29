#include "CrEngineInterface.h"

using namespace CreatorEngine;

int LCloseEngine(lua_State * L)
{
	int rlt = CloseEngine();

	lua_pushnumber(L, rlt);

	return 1;
}

int LInitEngine(lua_State * L)
{
	int rlt = InitEngine();

	lua_pushnumber(L, rlt);

	return 1;
}

void CreatorEngine::RegisterLuaAPI(lua_State * _L)
{
	LuaAPI_Register(_L, LInitEngine)
	LuaAPI_Register(_L, LCloseEngine)
}