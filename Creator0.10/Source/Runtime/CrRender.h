/*
CreatorEngine
Class CrEngineDevice
Payne
*/

#ifndef _CREATOR_RENDER_H
#define _CREATOR_RENDER_H

#include "CrDefine.h"
#include "CrModel.h"
#include "CrCamera.h"

class CrRender
{
public:
	CrRender();
	~CrRender();

public:
	EasyGetSet(GLuint, m_uiShader, Shader);
	void SetProjectionMatrix(glm::fmat4 * pfmat4);
	void SetViewMatrix(glm::fmat4 * pfmat4);
	void DrawTriangle(CrModel * pModel);
	void DrawCube(CrModel * pModel);
	void Draw(CrModel * pModel);
	bool Init();
private:
	GLuint m_uCurrentShader;

	glm::fmat4 m_m4MVP;
	glm::fmat4 m_m4View;
	glm::fmat4 m_m4Projection;
	glm::fmat4 m_m4Model;

	GLuint m_uMVP;
};

#endif