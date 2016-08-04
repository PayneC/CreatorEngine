#include "CrCanvas.h"
#include "CrEngine.h"

CrCanvas::CrCanvas()
{
	CrEngine::Instance()->AddCanvas(this);
}

CrCanvas::~CrCanvas()
{
	CrEngine::Instance()->RemoveCanvas(this);
}

void CrCanvas::Render()
{
	_Render(this);
}

void CrCanvas::_Render(CrGameObject * pGameObject)
{
//	if (pGameObject == NULL || !pGameObject->GetActive())
//		return;
//
//	CrMeshRender * meshRender = pGameObject->GetMeshRender();
//	CrTransform * transform = pGameObject->GetTransform();
//	if (meshRender != NULL && transform != NULL)
//	{
//		glm::mat4 mvp = GetVP() * transform->GetLocalToWorldMatrix();
//		meshRender->Draw(mvp);
//	}
//
//	std::vector<CrGameObject * > gameobjects = pGameObject->GetChildren();
//
//	std::vector<CrGameObject * >::iterator itor = gameobjects.begin();
//	std::vector<CrGameObject * >::iterator itorEnd = gameobjects.end();
//
//	CrGameObject * gameobject = NULL;
//	for (; itor != itorEnd; ++itor)
//	{
//		gameobject = (*itor);
//		_Render(gameobject);
//	}
}
