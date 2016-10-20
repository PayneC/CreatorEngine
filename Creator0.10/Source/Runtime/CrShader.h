/*
CreatorEngine
Class CrShader
Payne
*/

#ifndef _CREATOR_SHADER_H
#define _CREATOR_SHADER_H

#include <glew.h>
#include "CrDefine.h"
#include <CrObject.h>
#include <string>

/*
enum CrShaderPropertiesType
{
	INVALID = 0,
	Float = 1,
	Color = 2,
	Texture2D = 3,
	Texture3D = 4,
};

struct CrShaderProperties
{
public:
	CrShaderPropertiesType m_eType;
	std::string m_sName;
};

struct CrSPColor : CrShaderProperties
{
public:
	int32_t m_iColor;
};

struct CrSPFloat : CrShaderProperties
{
public:
	float m_fValue;
};

struct CrSPTexture2D
{
public:
	std::string m_sAssetsPath;
	CrTextureChunk * m_pTextur2D;
};
*/
class CrShader : CrObject
{
public:
	CrShader();
	~CrShader();

public:
	EasyGetSet(GLuint, m_uId, ID);
	EasyGetSet(GLuint, m_uShaderID, ShaderID);
	//void SetUniformMatrix4fv(GLuint location, glm::fmat4x4 * var);
private:	
	std::string m_sShaderName;
	//GLuint m_uShaderID;
};

#endif