#include "CrComponent.h"



CrComponent::CrComponent()
{
}


CrComponent::~CrComponent()
{
}
// void CrComponent::Awake()
// {
// 
// }
// void CrComponent::OnEnable()
// {
// 
// }
// void CrComponent::OnDisable()
// {
// 
// }
// void CrComponent::Update(float dt)
// {
// 
// }
// void CrComponent::LateUpdate(float dt)
// {
// 
// }
// void CrComponent::FixedUpdate(float dt)
// {
// 
// }
// void CrComponent::Destroy()
// {
// 
// }

void CrComponent::SetGameObject(CrGameObject * pointer)
{
	m_pGameObject = pointer;
}

CrGameObject * CrComponent::GetGameObject()
{
	return m_pGameObject;
}