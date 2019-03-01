#include <CrGameObject.h>

CrGameObject::CrGameObject()
	: m_isActive(true)
	, m_iTag(0)
	, m_ulLayer(0L)
	, m_kTransform(NULL)
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

void CrGameObject::_AddComponent(SharedPtr<CrComponent> Pointer)
{
	m_pComponents.push_back(Pointer);
	Pointer->SetGameObject(shared_from_this());
}
