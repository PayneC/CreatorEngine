/*
CreatorEngine
Class CrLua
Payne
*/

#ifndef _CREATOR_LUA_H
#define _CREATOR_LUA_H

#include <CrDefine.h>

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