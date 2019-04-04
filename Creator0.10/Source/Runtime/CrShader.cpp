#include "CrShader.h"

#include "CrDefine.h"
#include <string>
#include <fstream>

CrShader::CrShader()
	:m_bUseDepth(GL_TRUE)
	,m_eDepthFunc(GL_LESS)
{
}

CrShader::~CrShader()
{
}

void CrShader::BeginUse()
{
	glUseProgram(m_uShaderID);
	glDepthMask(m_bUseDepth);
	glDepthFunc(m_eDepthFunc);
}

void CrShader::EndUse()
{
	glUseProgram(0);	
}

