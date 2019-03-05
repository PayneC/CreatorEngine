/*
CreatorEngine
Class CrMaterial : CrObject
Payne
*/

#ifndef _CREATOR_MATERIAL_H
#define _CREATOR_MATERIAL_H

#include <CrShader.h>
#include <CrTexture.h>

enum EMaterialParameterType
{
	eInt,
	eFloat,
	eFloat2,
	eFloat3,
	eFloat4,
	eTexture,
};

__interface IMaterialParameter
{
	void * GetPtr();
	EMaterialParameterType GetType();
};

template<typename T>
class MaterialParameter : public IMaterialParameter
{
public:
	MaterialParameter(SharedPtr<T> ptr);
	~MaterialParameter();

	void * GetPtr();
	EMaterialParameterType GetType() { return eType; }

	EMaterialParameterType eType;
private:
	SharedPtr<T> _ptr;
};

class MatTextureParameter : public MaterialParameter<CrTexture>
{
public:
	MatTextureParameter(SharedPtr<CrTexture> ptr);
	~MatTextureParameter();

	GLenum TexIndex;
	Int Index;
private:

};

class DLL_ClASS CrMaterial : public CrObject
{
public:
	static SharedPtr<CrMaterial> CreateCrMaterial();

public:
	CrMaterial();
	~CrMaterial();	
	
	EasyGetSet(SharedPtr<CrShader>, m_pShader, Shader);
// 	EasyGet(glm::vec4 , m_dColor, Color);
// 	EasyGetSet(SharedPtr<CrTexture>, m_pMainTexture, pMainTexture);
// 	EasyGetSet(SharedPtr<CrTexture>, m_pNormalTexture, pNormalTexture);
// 	EasyGetSet(SharedPtr<CrTexture>, m_pSpecularTexture, pSpecularTexture);
	
	void SetInt(std::string name, Int value);
	void SetFloat(std::string name, Float value);
	void SetVector2(std::string name, Vector2f value);
	void SetVector3(std::string name, Vector3f value);
	void SetVector4(std::string name, Vector4f value);
	void SetColor(std::string name, Vector4f value);
	void SetTexture(std::string name, SharedPtr<CrTexture> value, GLenum e, Int index);

	void UploadUniform();
private:	

	std::map<std::string, IMaterialParameter*> _parameters;	
};
#endif
