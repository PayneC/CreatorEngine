#include "CrCamera.h"
#include "CrEngine.h"

CrCamera * CrCamera::Create()
{
	CrCamera * pRef = new CrCamera();
	if (!pRef)
	{
		CR_SAFE_DELETE(pRef);
	}
	pRef->Awake();
	return pRef;
}

CrCamera::CrCamera()
:m_m4ViewMatrix(1.f)
{
	m_pDrawTargets = std::list<CrModel*>();
	m_sName = "Camera";
}

CrCamera::~CrCamera()
{

}

void CrCamera::Update(float delay)
{
	CrGameObject::Update(delay);

	if (!m_isActive) 
		return;

	CrEngine::Director()->AddCamera(this);
}

void CrCamera::LookAt(CrGameObject * node)
{
	m_m4ViewMatrix = glm::lookAt(GetGlobalPosition(), node->GetGlobalPosition(), glm::fvec3(0.f, 1.f, 0.f));
}

