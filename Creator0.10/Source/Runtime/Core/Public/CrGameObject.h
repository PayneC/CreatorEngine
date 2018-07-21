/*
CreatorEngine
Class CrNode
Payne
*/

#ifndef _CREATOR_GAMEOBJECT_H
#define _CREATOR_GAMEOBJECT_H

#include <CrObject.h>
#include <CrTransform.h>


class DLL_ClASS CrGameObject : public CrObject, public std::enable_shared_from_this<CrGameObject>
{
public:
	template<typename TReturnType>
	static std::shared_ptr<TReturnType> CreateGameObject(std::string name = "gameobject");

	template<typename TReturnType>
	static std::shared_ptr<TReturnType> CreateGameObject(EPresetMeshType type, std::string name = "gameobject");

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
	std::shared_ptr<TReturnType> AddComponent();

	template<typename TReturnType>
	std::shared_ptr<TReturnType> GetComponent();

	std::shared_ptr<CrTransform> get_transform() { return m_kTransform; }
private:
	void _AddComponent(std::shared_ptr<CrComponent> Pointer);

protected:
	std::shared_ptr<CrTransform> m_kTransform;
	std::vector<std::shared_ptr<CrComponent>> m_pComponents;
};

template<typename TReturnType>
std::shared_ptr<TReturnType> CrGameObject::AddComponent()
{
	static_assert(std::is_base_of<CrComponent, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrComponent");

	std::shared_ptr<TReturnType> _instance = std::make_shared<TReturnType>();
	_AddComponent(_instance);
	return _instance;
}

template<typename TReturnType>
std::shared_ptr<TReturnType> CrGameObject::GetComponent()
{
	std::shared_ptr<TReturnType> _instance;
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
std::shared_ptr<TReturnType> CrGameObject::CreateGameObject(std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	std::shared_ptr<TReturnType> pRef = std::make_shared<TReturnType>();
	if (pRef)
	{		
		pRef->m_kTransform = pRef->AddComponent<CrTransform>();
		pRef->set_name(name);
	}
	return pRef;
}

template<typename TReturnType>
std::shared_ptr<TReturnType> CrGameObject::CreateGameObject(EPresetMeshType type, std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	std::shared_ptr<TReturnType> pRef = std::make_shared<TReturnType>();
	if (pRef)
	{
		pRef->m_kTransform = pRef->AddComponent<CrTransform>();
		pRef->set_name(name);
		std::shared_ptr<CrMeshRender> meshRender = pRef->AddComponent<CrMeshRender>();
		CrMaterial * material = CrMaterial::CreateCrMaterial();
		std::shared_ptr<CrMesh> mesh = CrMeshUtility::CreateMesh(type);
		CrShader * shader = CrShaderUtility::CreateShader("VertexLit.vert", "VertexLit.frag");
		material->SetShader(shader);
		meshRender->SetMaterial(material);
		meshRender->SetMesh(mesh);
	}
	return pRef;
}

#endif