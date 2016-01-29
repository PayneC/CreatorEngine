/*
CreatorEngine
Class CrNode
Payne
*/

#ifndef _CREATOR_GAMEOBJECT_H
#define _CREATOR_GAMEOBJECT_H

#include <map>
#include <list>
#include <vector>
#include <physX/PxPhysicsAPI.h>
#include <physX/vehicle/PxVehicleSDK.h>
#include <typeinfo.h>

#include <CrTransform.h>
#include <CrMeshRender.h>
#include <CrMeshFilter.h>

class CrGameObject : public CrObject
{
public:
	static CrGameObject * CreateGameObject();
	static CrGameObject * CreateGameObject(std::string name);
public:
	CrGameObject();
	~CrGameObject();
	
	void SetPosition(const glm::fvec3 & var);
	void SetRotation(const glm::fvec3 & var);
	void SetScaling(const glm::fvec3 & var);
	EasyGet(glm::fvec3, m_v3Position, Position);
	EasyGet(glm::fvec3, m_v3Rotation, Rotation);
	EasyGet(glm::fvec3, m_v3Scaling, Scaling);

	void SetGlobalPosition(const glm::fvec3 & var);
	void SetGlobalRotation(const glm::fvec3 & var);
	void SetGlobalScaling(const glm::fvec3 & var);

	glm::fvec3 GetGlobalPosition();
	glm::fvec3 GetGlobalRotation();
	glm::fvec3 GetGlobalScaling();

	virtual void ExecuteTranslate();						//实施变化

	virtual void Awake();
	virtual void Destroy();
	virtual void Update(float delay);

	virtual void OnEnter();
	virtual void Render();
	virtual void OnExit();
	
	void AddChild(CrGameObject * pNode);
	void RemoveChild(CrGameObject * pNode);
	void RemoveAllChild();

	EasyGetSetFuncOnly(CrGameObject *, m_pParent, Parent);
	EasyGetSet(int32_t, m_iTag, Tag);
	EasyGetSetFuncOnly(std::string, m_sName, Name);
	EasyGetSetFuncOnly(glm::fvec3, m_v3AnchorPoint, AnchorPoint);
	EasyGetSet(bool, m_isActive, Active);

	void LookAt(CrGameObject * node);

	template<typename TReturnType>
	TReturnType * AddComponent();

	template<typename TReturnType>
	TReturnType * GetComponent();

	EasyGet(CrTransform *, m_pTransform, Transform);
	EasyGet(CrMeshRender *, m_pMeshRender, MeshRender);
private:
	void AddComponent(CrComponent * Pointer);

private:
	std::vector<CrComponent*> m_pComponents;

protected:
	
	std::multimap<std::string, CrGameObject *> m_pChildren;
	std::multimap<std::string, CrGameObject *>::iterator m_itorChild;

// 	std::multimap<std::string, CrNode *> m_pChildren;
// 	std::multimap<std::string, CrNode *>::iterator m_itorChild;

	std::hash<size_t> m_pHash;

	//glm::vec3 m_v3Position;
	//glm::vec3 m_v3Rotation;
	//glm::vec3 m_v3Scaling;

	//glm::vec3 m_v3Position;
	//glm::vec3 m_v3Rotation;
	//glm::vec3 m_v3Scaling;

	glm::fvec4 m_v4AnchorPoint;
	bool m_isModified;
	
	//glm::mat4 m_m4Position;
	//glm::mat4 m_m4Rotation;
	//glm::mat4 m_m4Scaling;
	//glm::mat4 m_m4Transform;
	glm::fmat4 m_m4Transform;
	glm::fmat4 m_m4AnchorOffset;

	glm::fvec3 m_v3LocalCoordinate;


};

template<typename TReturnType>
TReturnType * CrGameObject::AddComponent()
{
	//static_assert(std::is_base_of<CrComponent, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from UActorComponent");
	static_assert(std::is_base_of<CrComponent, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from UActorComponent");
	
	TReturnType* _instance = new TReturnType();
	AddComponent(_instance);
	return _instance;
}

template<typename TReturnType>
TReturnType * CrGameObject::GetComponent()
{
	TReturnType* _instance = NULL;
	for (auto& component : m_pComponents)
	{
		if (component &&  typeid(*component) == typeid(TReturnType))
		{
			_instance = component;
			break;
		}	
	}
	return _instance;
}

#endif