/*
CreatorEngine
Class CrCamera
Payne
*/

#ifndef _CREATOR_CAMERA_H
#define _CREATOR_CAMERA_H

#include <CrGameObject.h>

class DLL_ClASS CrCamera : public CrGameObject
{
private:
	static std::list<CrCamera*> m_pCameraList;
public:
	static std::list<CrCamera*> AllCamera();

public:
	CrCamera();
	~CrCamera();

	glm::mat4 GetVP();

	EasyGetSet(GLshort, m_sProjection, Projection);
private:
	glm::fmat4 m_m4Projection;
	glm::fmat4 m_m4VP;	
};

#endif