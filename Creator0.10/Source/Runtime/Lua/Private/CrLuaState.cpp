#include "CrLuaState.h"
using namespace CreatorLua;

CrLuaState::CrLuaState()
{

}

CrLuaState::~CrLuaState()
{

}

bool CrLuaState::Init()
{
	_L = luaL_newstate();
	luaL_openlibs(_L);
	
	luaL_dofile(_L, "main.lua");
	lua_getglobal(_L, "main");
	lua_pcall(_L, 0, 0, 0);
	return true;
}

void CrLuaState::Main()
{

}

int CrLuaState::DoLuaFunction(std::string path, std::string functionName)
{
	return 0;
}
