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
public:
	static std::list<std::shared_ptr<CrCamera>> m_pCameraList;
	static std::list<std::shared_ptr<CrCamera>> AllCamera();

public:
	CrCamera();
	~CrCamera();

	glm::mat4 GetVP();
	glm::mat4 GetP() { return m_m4Projection; }
	EasyGetSet(GLshort, m_sProjection, Projection);		

private:
	glm::fmat4 m_m4Projection;
	glm::fmat4 m_m4VP;	
};

#endif