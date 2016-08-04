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

void CrGameObject::_AddComponent(CrComponent * Pointer)
{
	m_pComponents.push_back(Pointer);
	Pointer->SetGameObject(this);
	Pointer->Retain();

	if (typeid(*Pointer) == typeid(CrMeshRender))
	{
		m_pMeshRender = (CrMeshRender * )Pointer;
	}
}
