/*
CreatorEngine
Class CrNode
Payne
*/

#ifndef _CREATOR_GAMEOBJECT_H
#define _CREATOR_GAMEOBJECT_H

#include <CrObject.h>
#include <CrTransform.h>

//using namespace CreatorEngine;

class DLL_ClASS CrGameObject : public CrObject, public std::enable_shared_from_this<CrGameObject>
{	
public:
	template<typename TReturnType>
	static SharedPtr<TReturnType> CreateGameObject(std::string name = "gameobject");

	template<typename TReturnType>
	static SharedPtr<TReturnType> CreateGameObject(EPresetMeshType type, std::string name = "gameobject");

public:
	CrGameObject();
	~CrGameObject();

	virtual void Start();
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

	EasyGetSet(int32_t, m_iTag, Tag);
	EasyGetSet(bool, m_isActive, Active);
	EasyGetSet(uint64_t, m_ulLayer, Layer);

	template<typename TReturnType>
	SharedPtr<TReturnType> AddComponent();

	template<typename TReturnType>
	SharedPtr<TReturnType> GetComponent();

	SharedPtr<CrTransform> get_transform() { return m_kTransform; }

	void SetParent(SharedPtr<CrGameObject> pParent);
	void RemoveChild(SharedPtr<CrGameObject> pChild);

	void RemoveAllChild();
private:
	void _AddComponent(SharedPtr<CrComponent> Pointer);

protected:
	SharedPtr<CrTransform> m_kTransform;
	std::vector<SharedPtr<CrComponent>> m_pComponents;

	WeakPtr<CrGameObject> m_pParent;
	std::vector<SharedPtr<CrGameObject>> m_pChildren;
};

template<typename TReturnType>
SharedPtr<TReturnType> CrGameObject::AddComponent()
{
	static_assert(std::is_base_of<CrComponent, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrComponent");

	SharedPtr<TReturnType> _instance = std::make_shared<TReturnType>();
	_AddComponent(_instance);
	return _instance;
}

template<typename TReturnType>
SharedPtr<TReturnType> CrGameObject::GetComponent()
{
	SharedPtr<TReturnType> _instance;
	for (auto& component : m_pComponents)
	{
		if (component &&  typeid(*component) == typeid(TReturnType))
		{
			_instance = std::dynamic_pointer_cast<TReturnType>(component);
			break;
		}
	}
	return _instance;
}


template<typename TReturnType>
SharedPtr<TReturnType> CrGameObject::CreateGameObject(std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	SharedPtr<TReturnType> pRef = std::make_shared<TReturnType>();
	if (pRef)
	{		
		pRef->m_kTransform = pRef->AddComponent<CrTransform>();
		pRef->set_name(name);		
	}
	return pRef;
}

template<typename TReturnType>
SharedPtr<TReturnType> CrGameObject::CreateGameObject(EPresetMeshType type, std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	SharedPtr<TReturnType> pRef = std::make_shared<TReturnType>();
	if (pRef)
	{
		pRef->m_kTransform = pRef->AddComponent<CrTransform>();
		pRef->set_name(name);
		SharedPtr<CrMeshRender> meshRender = pRef->AddComponent<CrMeshRender>();
		SharedPtr<CrMaterial> material = CrMaterial::CreateCrMaterial();
		SharedPtr<CrMesh> mesh = CrMeshUtility::CreateMesh(type);
		SharedPtr<CrShader> shader = CrShaderUtility::CreateShader("VertexLit.vert", "VertexLit.frag");
		material->SetShader(shader);
		meshRender->SetMaterial(material);
		meshRender->SetMesh(mesh);		
	}
	return pRef;
}

#endif