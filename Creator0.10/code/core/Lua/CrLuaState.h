/*
CreatorEngine
Class CrLua
Payne
*/

#ifndef _CREATOR_LUA_H
#define _CREATOR_LUA_H

#include "../CrSingleton.h"
#include <lua\src\lua.hpp>
#include <string>
#include <stdarg.h>

namespace CreatorLua
{
	class CrLuaState
	{
	public:
		CrLuaState();
		~CrLuaState();

	public:
		bool Init();
		void Main();
		int DoLuaFunction(std::string path, std::string functionName);
	private:
		lua_State * _L;
	};
}

#endif