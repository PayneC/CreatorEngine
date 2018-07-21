#include <CrCamera.h>
#include <CrTransform.h>

CrCamera::CrCamera()
	:m_m4Projection(1.f)
	, m_sProjection(CAMERA_PROJECTION_PERSPECTIVE)
{	
	m_m4Projection = glm::perspective(45.f, 16.f / 9.f, 0.1f, 200.f);
}

CrCamera::~CrCamera()
{
	m_pCameraList.remove(std::dynamic_pointer_cast<CrCamera>(shared_from_this()));
}

glm::mat4 CrCamera::GetVP()
{
	m_m4VP = m_m4Projection * get_transform()->GetWorldToLocalMatrix();
	return m_m4VP;
}

std::list<std::shared_ptr<CrCamera>> CrCamera::m_pCameraList;

std::list<std::shared_ptr<CrCamera>> CrCamera::AllCamera()
{
	return m_pCameraList;
}