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
#include <typeinfo.h>

#include <Component\CrTransform.h>
#include <Component\CrMeshRender.h>

class DLL_ClASS CrGameObject : public CrObject
{
public:
	template<typename TReturnType>
	static TReturnType * CreateGameObject(std::string name = "gameobject");

	template<typename TReturnType>
	static TReturnType * CreateGameObject(EPresetMeshType type, std::string name = "gameobject");

public:
	CrGameObject();
	~CrGameObject();
	
	virtual void Awake();
	virtual void Begin();
	virtual void Destroy();
	virtual void Update();
	virtual void Enable();
	virtual void Disabled();
	
	void AddChild(CrGameObject * pNode);
	void RemoveChild(CrGameObject * pNode);
	void RemoveAllChild();

	EasyGetSetFuncOnly(CrGameObject *, m_pParent, Parent);
	EasyGetSet(int32_t, m_iTag, Tag);
	EasyGetSetFuncOnly(std::string, m_sName, Name);
	EasyGetSet(bool, m_isActive, Active);
	EasyGetSet(uint64_t, m_ulLayer, Layer);

	template<typename TReturnType>
	TReturnType * AddComponent();

	template<typename TReturnType>
	TReturnType * GetComponent();

	void RemoveComponent(CrComponent * Pointer);
	void RemoveAllComponent();

	EasyGet(CrTransform *, m_kTransform, Transform);
	EasyGet(CrMeshRender *, m_pMeshRender, MeshRender);

	const std::vector<CrGameObject *> GetChildren() const { return m_pChildren; }

private:
	void _AddComponent(CrComponent * Pointer);
	
protected:
	std::vector<CrComponent *> m_pComponents;
	std::vector<CrGameObject *> m_pChildren;
};

template<typename TReturnType>
TReturnType * CrGameObject::AddComponent()
{
	static_assert(std::is_base_of<CrComponent, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrComponent");
	
	TReturnType* _instance = new TReturnType();
	_instance->Awake();
	_AddComponent(_instance);
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
			_instance = (TReturnType * )component;
			break;
		}	
	}
	return _instance;
}


template<typename TReturnType>
TReturnType * CrGameObject::CreateGameObject(std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	TReturnType * pRef = new TReturnType();
	if (pRef)
	{
		pRef->SetName(name);
		pRef->Awake();
	}
	return pRef;
}

template<typename TReturnType>
TReturnType * CrGameObject::CreateGameObject(EPresetMeshType type, std::string name)
{
	static_assert(std::is_base_of<CrGameObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrGameObject");

	TReturnType * pRef = new TReturnType();
	if (pRef)
	{
		pRef->SetName(name);
		pRef->Awake();
		CrMeshRender * meshRender = pRef->AddComponent<CrMeshRender>();
		CrMaterial * material = CrMaterial::CreateCrMaterial();
		CrMesh * mesh = CrMeshUtility::CreateMesh(type);
		CrShader * shader = CrShaderUtility::CreateShader("VertexLit.vert", "VertexLit.frag");
		material->SetShader(shader);
		meshRender->SetMaterial(material);
		meshRender->SetMesh(mesh);
	}
	return pRef;
}

#endif