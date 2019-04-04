#include <CrComponent.h>

CrComponent::CrComponent()
{
}


CrComponent::~CrComponent()
{
}

void CrComponent::Awake()
{
}

void CrComponent::Start()
{

}

void CrComponent::Update(double dt)
{

}

void CrComponent::LateUpdate(double dt)
{

}

void CrComponent::OnEnable()
{

}

void CrComponent::OnDisable()
{

}

void CrComponent::OnDestroy()
{

}

void CrComponent::SetGameObject(std::shared_ptr<CrGameObject> pointer)
{
	m_pGameObject = pointer;
}

std::shared_ptr<CrGameObject> CrComponent::GetGameObject()
{
	return m_pGameObject.lock();
}
