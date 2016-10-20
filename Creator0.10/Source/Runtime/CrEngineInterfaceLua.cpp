#include  <CrEngineInterfaceLua.h>
#include <CrEngineInterface.h>

using namespace CreatorEngineLua;

int CreatorEngineLua::Stop(lua_State * L)
{
	CreatorEngine::Stop();

	lua_pushnumber(L, 0);

	return 1;
}

int CreatorEngineLua::Initialization(lua_State * L)
{
	int rlt = CreatorEngine::Initialization();

	lua_pushnumber(L, rlt);

	return 1;
}

void CreatorEngineLua::RegisterLuaAPI(lua_State * _L)
{
	LuaAPI_Register(_L, Stop);
	LuaAPI_Register(_L, Initialization);
}