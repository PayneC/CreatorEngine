/*
CreatorEngine
Class CrCamera
Payne
*/

#ifndef _CREATOR_CAMERA_H
#define _CREATOR_CAMERA_H

#include <Core/CrScene.h>

class DLL_ClASS CrCamera : public CrGameObject
{
public:
	CrCamera();
	~CrCamera();

	glm::mat4 GetVP();

	EasyGetSet(GLshort, m_sProjection, Projection);

	void Render(CrScene * pScene);
	void _Render(CrGameObject * pGameObject);
private:
	glm::fmat4 m_m4Projection;
	glm::fmat4 m_m4VP;	
};

#endif