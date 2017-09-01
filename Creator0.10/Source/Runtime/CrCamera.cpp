#include "CrCamera.h"
#include "CrEngine.h"

CrCamera::CrCamera()
	:m_m4Projection(1.f)
	, m_sProjection(CAMERA_PROJECTION_PERSPECTIVE)
{
	m_sName = "Camera";
	m_m4Projection = glm::perspective(45.f, 16.f / 9.f, 0.1f, 200.f);
	CrEngine::Instance()->AddCamera(this);
}

CrCamera::~CrCamera()
{
	CrEngine::Instance()->RemoveCamera(this);
}

glm::mat4 CrCamera::GetVP()
{
	m_m4VP = m_m4Projection * GetTransform()->GetWorldToLocalMatrix();
	return m_m4VP;
}

void CrCamera::Render(CrScene * pScene)
{
	_Render(pScene);
}

void CrCamera::_Render(CrGameObject * pGameObject)
{
	if (pGameObject == NULL || !pGameObject->GetActive())
		return;

	CrMeshRender * meshRender = pGameObject->GetMeshRender();
	CrTransform * transform = pGameObject->GetTransform();
	if (meshRender != NULL && transform != NULL)
	{
		glm::mat4 mvp = GetVP() * transform->GetLocalToWorldMatrix();
		meshRender->Draw(mvp, GetTransform()->GetForword());
	}

	std::vector<CrGameObject * > gameobjects = pGameObject->GetChildren();

	std::vector<CrGameObject * >::iterator iter = gameobjects.begin();
	std::vector<CrGameObject * >::iterator iterEnd = gameobjects.end();

	CrGameObject * gameobject = NULL;
	for (; iter != iterEnd; ++iter)
	{
		gameobject = (*iter);
		_Render(gameobject);
	}
}
