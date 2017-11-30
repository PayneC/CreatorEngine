#include <CrCamera.h>
#include <CrTransform.h>

CrCamera::CrCamera()
	:m_m4Projection(1.f)
	, m_sProjection(CAMERA_PROJECTION_PERSPECTIVE)
{
	m_sName = "Camera";
	m_m4Projection = glm::perspective(45.f, 16.f / 9.f, 0.1f, 200.f);
	m_pCameraList.push_back(this);
}

CrCamera::~CrCamera()
{
	m_pCameraList.remove(this);
}

glm::mat4 CrCamera::GetVP()
{
	m_m4VP = m_m4Projection * GetTransform()->GetWorldToLocalMatrix();
	return m_m4VP;
}

std::list<CrCamera*> CrCamera::m_pCameraList;

std::list<CrCamera*> CrCamera::AllCamera()
{
	return m_pCameraList;
}