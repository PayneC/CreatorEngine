/*
CreatorEngine
CrDefine
Payne
*/

#ifndef _CREATOR_DEFINE_H
#define _CREATOR_DEFINE_H

#include <thread>

#include <cstdio>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <string>
#include <stdarg.h>

#include <map>
#include <list>
#include <vector>
#include <typeinfo.h>

//Math
#include <glm/glm/glm.hpp>
#include <glm/glm/fwd.hpp>
#include <glm/glm/gtc/type_ptr.hpp> 
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>

#include <glew/include/GL/glew.h>
#include <glfw3/include/GLFW/glfw3.h>

#include <SOIL/include/SOIL.h>
#include <lua/src/lua.hpp>

#include <CrSingleton.h>

#define EasyGetSet(varType, varName, funName)\
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }

#define EasyGet(varType, varName, funName)\
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; }

#define EasyGetFuncOnly(varType, varName, funName)\
protected: varType varName; \
public: virtual varType Get##funName(void);

#define EasyGetSetFuncOnly(varType, varName, funName)\
protected: varType varName; \
public: virtual varType Get##funName(void); \
public: virtual void Set##funName(varType var);

#define FuncGetSet(varType, funName)\
public: virtual varType Get##funName(void); \
public: virtual void Set##funName(varType var);

#define CR_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define CR_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define CR_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define CR_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define CR_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define CR_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define CR_BREAK_IF(cond)            if(cond) break

#define CR_FIWORD(param)           ((__int16)(((__int64)(param)) & 0xffff))
#define CR_SEWORD(param)           ((__int16)((((__int64)(param)) >> 16) & 0xffff))
#define CR_THWORD(param)           ((__int16)((((__int64)(param)) >> 32) & 0xffff))
#define CR_FOWORD(param)           ((__int16)((((__int64)(param)) >> 48) & 0xffff))

//Event
#define CR_EVENT_NONE						0	
#define CR_EVENT_KEY						1
#define CR_EVENT_MOUSE_BUTTON				2
#define CR_EVENT_MOUSE_MOVE					3
#define CR_EVENT_JOYSTICK					4

#define LuaAPI_Register(l,f) lua_register(l, #f, f);	

enum EPresetMeshType
{
	CR_MESH_TYPE_CUBE = 0,
	CR_MESH_TYPE_QUAD = 1,
};
#define CR_MESH_TYPE_COUNT					2	

#define CAMERA_PROJECTION_PERSPECTIVE		1
#define CAMERA_PROJECTION_ORTHOGRAPHIC		2

#define Vector2 glm::vec2
#define Vector3 glm::vec3

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
};

#ifdef DLL_EXPORT
#define DLL_ClASS _declspec(dllexport)
#else
#define DLL_ClASS _declspec(dllimport) 
#endif // DLL_IMPORT


#endif