#include <CrGameObject.h>

CrGameObject::CrGameObject()
	: m_isActive(true)
	, m_iTag(0)
	, m_ulLayer(0L)
	, m_kTransform(NULL)
	, m_pChildren()
{
	
}

CrGameObject::~CrGameObject()
{
}

void CrGameObject::Start()
{

}

void CrGameObject::Update(double dt)
{
	if (!m_isActive) return;

	std::vector<std::shared_ptr<CrComponent>>::iterator icom = m_pComponents.begin();
	std::vector<std::shared_ptr<CrComponent>>::iterator icomend = m_pComponents.end();
	for (; icom != icomend; ++icom)
	{
		(*icom)->Update(dt);
	}
}

void CrGameObject::LateUpdate(double dt)
{

}

void CrGameObject::OnEnable()
{

}

void CrGameObject::OnDisable()
{

}

void CrGameObject::OnDestroy()
{

}

void CrGameObject::SetParent(SharedPtr<CrGameObject> pParent)
{
	SharedPtr<CrGameObject> _parent = m_pParent.lock();
	if (_parent == pParent)
	{
		return;
	}

	if (_parent != nullptr)
	{
		_parent->RemoveChild(shared_from_this());
	}

	_parent = pParent;

	if (_parent != nullptr)
	{
		_parent->m_pChildren.push_back(shared_from_this());
	}

	m_pParent = _parent->weak_from_this();

	m_kTransform->SetParent(pParent->m_kTransform);
}

void CrGameObject::RemoveChild(SharedPtr<CrGameObject> pChild)
{
	if (!pChild)
		return;

	std::vector<SharedPtr<CrGameObject>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrGameObject>>::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == pChild)
			break;
	}
	if (iter != iterEnd)
	{
		m_pChildren.erase(iter);
	}
	pChild->m_pParent.expired();

	m_kTransform->RemoveChild(pChild->m_kTransform);
}

void CrGameObject::RemoveAllChild()
{
	std::vector<SharedPtr<CrGameObject>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrGameObject>>::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		SharedPtr<CrGameObject> child = (*iter);
		child->m_pParent.expired();
	}

	m_pChildren.clear();
	m_kTransform->RemoveAllChild();
}

void CrGameObject::_AddComponent(SharedPtr<CrComponent> Pointer)
{
	m_pComponents.push_back(Pointer);
	Pointer->SetGameObject(shared_from_this());
	Pointer->Awake();
}