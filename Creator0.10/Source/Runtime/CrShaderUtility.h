/*
CreatorEngine
Class CrShader
Payne
*/

#ifndef _CREATOR_SHADERUTILITY_H
#define _CREATOR_SHADERUTILITY_H 

#include <CrDefine.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "CrShader.h"
#include "CrSingleton.h"

class DLL_ClASS CrShaderUtility : public CrSingleton<CrShaderUtility>
{
public:
	static SharedPtr<CrShader> CreateShader(const char * vertexFile, const char * fragmentFile);
public:
	CrShaderUtility();
	~CrShaderUtility();

	bool Init();
	void Destory();

	SharedPtr<CrShader> Find(std::string name);	
	void Remove(std::string name);
	void RemoveAll();

private:
	SharedPtr<CrShader> _CreateShader(const char * vertexFile, const char * fragmentFile);
	GLuint CompileShader(const char * vertexFile, const char * fragmentFile);
private:
	std::map<std::string, SharedPtr<CrShader>> m_shaders;
	std::map<std::string, SharedPtr<CrShader>>::iterator m_iterShader;
};

#endif