/*
CreatorEngine
Class CrShader
Payne
*/

#ifndef _CREATOR_SHADER_H
#define _CREATOR_SHADER_H

#include <CrObject.h>

class DLL_ClASS CrShader : CrObject
{
public:
	CrShader();
	~CrShader();

public:	
	EasyGetSet(GLuint, m_uShaderID, ShaderID);
	EasyGetSet(GLboolean, m_bUseDepth, UseDepth);
	EasyGetSet(GLenum, m_eDepthFunc, DepthFunc);

	void BeginUse();
	void EndUse();	
private:	
	std::string m_sShaderName;	
};

#endif