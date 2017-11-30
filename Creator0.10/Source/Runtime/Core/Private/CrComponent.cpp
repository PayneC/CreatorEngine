#include <CrComponent.h>

CrComponent::CrComponent()
{
}


CrComponent::~CrComponent()
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

void CrComponent::SetGameObject(CrGameObject * pointer)
{
	m_pGameObject = pointer;
}

CrGameObject * CrComponent::GetGameObject()
{
	return m_pGameObject;
}