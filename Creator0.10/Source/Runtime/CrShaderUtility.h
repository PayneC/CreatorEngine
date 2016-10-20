/*
CreatorEngine
Class CrShader
Payne
*/

#ifndef _CREATOR_SHADERUTILITY_H
#define _CREATOR_SHADERUTILITY_H

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "CrShader.h"
#include "CrSingleton.h"

class CrShaderUtility : public CrSingleton<CrShaderUtility>
{
public:
	static CrShader * CreateShader(const char * vertexFile, const char * fragmentFile);
public:
	CrShaderUtility();
	~CrShaderUtility();

	bool Init();
	void Destory();

	bool Find(std::string name, GLuint *id);
	GLuint Insert(std::string name, const char * vertexFile, const char * fragmentFile);
	void Remove(std::string name);
	void RemoveAll();

private:
	CrShader * _CreateShader(const char * vertexFile, const char * fragmentFile);
	GLuint CompileShader(const char * vertexFile, const char * fragmentFile);
private:	
	std::map<std::string, GLuint> m_shaders;
	std::map<std::string, GLuint>::iterator m_iterShader;
};

#endif