#include "CrGameObject.h"


CrGameObject::CrGameObject()
: m_isActive(true)
, m_sName("GameObject")
, m_isModified(true)
, m_m4Transform(1.0f)
, m_v3Scaling(1.0f)
, m_v3Rotation(0.f)
, m_v3Position(0.f)
, m_v4AnchorPoint(1.f)
, m_v3AnchorPoint(0.f)
{
}

CrGameObject::~CrGameObject()
{
}

void CrGameObject::SetPosition(const glm::fvec3 & v3Position)
{
	if (m_v3Position != v3Position)
	{
		m_v3Position = v3Position;
		m_isModified = true;
	}
}

void CrGameObject::SetRotation(const glm::fvec3 & v3Rotation)
{
	if (m_v3Rotation != v3Rotation)
	{
		m_v3Rotation = v3Rotation;
		m_isModified = true;
	}
}

void CrGameObject::SetScaling(const glm::fvec3 & v3Scaling)
{
	if (m_v3Scaling != v3Scaling)
	{
		m_v3Scaling = v3Scaling;
		m_isModified = true;
	}
}

void CrGameObject::ExecuteTranslate()
{
	m_m4Transform = glm::mat4(glm::quat(m_v3Rotation));
	m_m4Transform = glm::scale(m_m4Transform, m_v3Scaling);
	m_m4Transform = glm::translate(m_m4Transform, m_v3Position);

	//m_m4Transform = m_m4RotateX * m_m4RotateY * m_m4RotateZ * m_m4Scaling * m_m4Translate;
	if (m_pParent)
		m_m4Transform *= m_pParent->m_m4Transform;

	m_itorChild = m_pChildren.begin();
	for (; m_itorChild != m_pChildren.end(); ++m_itorChild)
	{
		m_itorChild->second->m_isModified = true;
	}

	m_isModified = false;

#ifdef _CR_DEBUG
	printf("%s: pos (%f,%f,%f)\n", m_sName.c_str(), m_v3Position.x, m_v3Position.y, m_v3Position.z);
#endif
}

void CrGameObject::Awake()
{

}

void CrGameObject::Destroy()
{
	if (m_pParent)
		m_pParent->RemoveChild(this);

	RemoveAllChild();
}

void CrGameObject::Update(float delay)
{
	if (!m_isActive) return;

	if (m_isModified)
		ExecuteTranslate();

	m_itorChild = m_pChildren.begin();
	for (; m_itorChild != m_pChildren.end(); ++m_itorChild)
	{
		m_itorChild->second->Update(delay);
	}
}

void CrGameObject::Render()
{
	if (!m_isActive) return;

	m_itorChild = m_pChildren.begin();
	for (; m_itorChild != m_pChildren.end(); ++m_itorChild)
	{
		m_itorChild->second->Render();
	}
}

void CrGameObject::OnEnter()
{

}

void CrGameObject::OnExit()
{

}

void CrGameObject::AddChild(CrGameObject * pNode)
{
	if (NULL == pNode || pNode->m_pParent == this)
		return;
	
	if (pNode->m_pParent)
		pNode->m_pParent->RemoveChild(this);

	m_pChildren.insert(std::pair<std::string, CrGameObject *>(pNode->m_sName, pNode));
	pNode->m_pParent = this;
	pNode->Retain();
}

void CrGameObject::RemoveChild(CrGameObject * pNode)
{
	if (!pNode)
		return;

	std::multimap<std::string, CrGameObject *>::iterator end;
	end = m_pChildren.upper_bound(pNode->m_sName);
	m_itorChild = m_pChildren.lower_bound(pNode->m_sName);

	for (; m_itorChild != end; ++m_itorChild)
	{
		if (m_itorChild->second == pNode)
		{
			m_pChildren.erase(m_itorChild);
			pNode->Release();
			break;
		}
	}
}

void CrGameObject::RemoveAllChild()
{
	m_itorChild = m_pChildren.begin();
	for (; m_itorChild != m_pChildren.end(); ++m_itorChild)
	{
		m_itorChild->second->Release();
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


glm::fvec3 CrGameObject::GetGlobalPosition()
{
	if (m_isModified)
	{
		ExecuteTranslate();
	}
	glm::fvec4 v4(m_v3Position, 1.0f);
	v4 = m_m4Transform * v4;
	glm::fvec3 v3(v4);
	return v3;
}

glm::fvec3 CrGameObject::GetGlobalRotation()
{

	if (m_isModified)
	{
		ExecuteTranslate();
	}
	glm::fvec4 v4(m_v3Position, 1.0f);
	v4 = m_m4Transform * v4;
	glm::fvec3 v3(v4);
	return v3;
}

glm::fvec3 CrGameObject::GetGlobalScaling()
{

	if (m_isModified)
	{
		ExecuteTranslate();
	}
	glm::fvec4 v4(m_v3Position, 1.0f);
	v4 = m_m4Transform * v4;
	glm::fvec3 v3(v4);
	return v3;
}

void CrGameObject::SetGlobalPosition(const glm::fvec3 & var)
{
	
}

void CrGameObject::SetGlobalRotation(const glm::fvec3 & var)
{
	
}

void CrGameObject::SetGlobalScaling(const glm::fvec3 & var)
{
	
}

void CrGameObject::SetAnchorPoint(glm::fvec3 var)
{
	m_v3AnchorPoint = var;
}

glm::fvec3 CrGameObject::GetAnchorPoint()
{
	return m_v3AnchorPoint;
}

void CrGameObject::LookAt(CrGameObject * node)
{

}

void CrGameObject::AddComponent(CrComponent * Pointer)
{
	m_pComponents.push_back(Pointer);
	Pointer->SetGameObject(this);
	Pointer->Retain();
}

CrGameObject * CrGameObject::CreateGameObject()
{
	CrGameObject * _instance = new CrGameObject();//CrObject::Instance<CrGameObject>();
	if (_instance)
		_instance->Awake();
	return _instance;
}

CrGameObject * CrGameObject::CreateGameObject(std::string name)
{
	CrGameObject * _instance = new CrGameObject();//CrObject::Instance<CrGameObject>();
	if (_instance)
	{
		_instance->SetName(name);
		_instance->Awake();
	}		
	return _instance;
}