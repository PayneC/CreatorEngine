/*
CreatorEngine
Class CrShader
Payne
*/

#ifndef _CREATOR_SHADERFACTORY_H
#define _CREATOR_SHADERFACTORY_H

#include <glew\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "CrShader.h"

class CrShaderUtility
{
	friend class CrEngine;
private:
	CrShaderUtility();
	bool Init();
	void Destory();

public:
	~CrShaderUtility();

	GLuint Find(std::string name);
	GLuint Insert(std::string name, const char * vertexFile, const char * fragmentFile);
	void Remove(std::string name);
	void RemoveAll();

	CrShader * CreateShader(const char * vertexFile, const char * fragmentFile);
	GLuint CompileShader(const char * vertexFile, const char * fragmentFile);
private:	
	std::map<std::string, GLuint> m_shaders;
	std::map<std::string, GLuint>::iterator m_iterShader;
};

#endif