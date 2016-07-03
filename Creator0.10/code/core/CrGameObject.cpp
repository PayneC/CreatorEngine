#include "CrGameObject.h"
#include "CrMeshUtility.h"
#include "CrShaderUtility.h"

CrGameObject::CrGameObject()
: m_isActive(true)
, m_sName("GameObject")
{
	m_kTransform = AddComponent<CrTransform>();
}

CrGameObject::~CrGameObject()
{
}

void CrGameObject::Awake()
{

}

void CrGameObject::Begin()
{

}

void CrGameObject::Destroy()
{
	if (m_pParent)
		m_pParent->RemoveChild(this);

	RemoveAllChild();
}

void CrGameObject::Update()
{
	if (!m_isActive) return;

	std::vector<CrComponent*>::iterator icom = m_pComponents.begin();
	std::vector<CrComponent*>::iterator icomend = m_pComponents.end();
	for (; icom != icomend; ++icom)
	{
		(*icom)->Update();
	}

	std::vector<CrGameObject * >::iterator itor = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator itorEnd = m_pChildren.end();
	for (; itor != itorEnd; ++itor)
	{
		(*itor)->Update();
	}
}

void CrGameObject::Enable()
{

}

void CrGameObject::Disabled()
{

}

void CrGameObject::Render(glm::fmat4 & vp)
{
#ifdef OLD
	if (!m_isActive) return;

	m_itorChild = m_pChildren.begin();
	for (; m_itorChild != m_pChildren.end(); ++m_itorChild)
	{
		m_itorChild->second->Render();
	}
#else
	if (!m_isActive) return;

	std::vector<CrGameObject * >::iterator itor = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator itorEnd = m_pChildren.end();
	for (; itor != itorEnd; ++itor)
	{
		(*itor)->Render(vp);
	}

	if (m_pMeshRender == NULL)
	{
		m_pMeshRender = GetComponent<CrMeshRender>();
	}
	if (m_pMeshRender)
	{
		glm::mat4 mvp = vp * m_kTransform->GetLocalToWorldMatrix();
		glm::vec4 p = mvp * glm::vec4(0.f, 0.f, 1.f, 1.f);
		m_pMeshRender->Draw(mvp);
	}
		
#endif
}

void CrGameObject::AddChild(CrGameObject * pNode)
{
	if (NULL == pNode || pNode->m_pParent == this)
		return;
	
	if (pNode->m_pParent)
		pNode->m_pParent->RemoveChild(this);

	m_pChildren.push_back(pNode);
	pNode->m_pParent = this;
	pNode->Retain();
}

void CrGameObject::RemoveChild(CrGameObject * pNode)
{
	if (!pNode)
		return;

	std::vector<CrGameObject * >::iterator itor = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator itorEnd = m_pChildren.end();
	for (; itor != itorEnd; ++itor)
	{
		if ((*itor) == pNode)
			break;
	}
	if (itor != itorEnd)
	{
		m_pChildren.erase(itor);
		pNode->Release();
	}
}

void CrGameObject::RemoveAllChild()
{
	std::vector<CrGameObject * >::iterator itor = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator itorEnd = m_pChildren.end();
	for (; itor != itorEnd; ++itor)
	{
		(*itor)->Release();
	}

	m_pChildren.clear();
}

void CrGameObject::SetName(std::string var)
{
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
		m_sName = var;
		m_pParent->AddChild(this);
	}
	else
	{
		m_sName = var;
	}
}

std::string CrGameObject::GetName()
{
	return m_sName;
}

void CrGameObject::SetParent(CrGameObject * pNode)
{
	pNode->AddChild(this);
}

CrGameObject * CrGameObject::GetParent()
{
	return m_pParent;
}

void CrGameObject::AddComponent(CrComponent * Pointer)
{
	m_pComponents.push_back(Pointer);
	Pointer->SetGameObject(this);
	Pointer->Retain();

	if (typeid(*Pointer) == typeid(CrMeshRender))
	{
		m_pMeshRender = (CrMeshRender * )Pointer;
	}
}
