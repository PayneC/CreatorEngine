#include <CrMaterial.h>

template<typename T>
inline MaterialParameter<T>::MaterialParameter(SharedPtr<T> ptr)
{
	_ptr = ptr;
}

template<typename T>
inline MaterialParameter<T>::~MaterialParameter()
{
}

MatTextureParameter::MatTextureParameter(SharedPtr<CrTexture> ptr)	
	:MaterialParameter(ptr)
{

}

MatTextureParameter::~MatTextureParameter()
{
}

template<typename T>
void * MaterialParameter<T>::GetPtr()
{
	return (void *)_ptr.get();
}

SharedPtr<CrMaterial> CrMaterial::CreateCrMaterial()
{
	SharedPtr<CrMaterial> _instance = std::make_shared<CrMaterial>();
	return _instance;
}

CrMaterial::CrMaterial()
	:m_pShader(0)
{
}

CrMaterial::~CrMaterial()
{
	std::map<std::string, IMaterialParameter*>::iterator beginIt = _parameters.begin();
	std::map<std::string, IMaterialParameter*>::iterator endIt = _parameters.end();

	while (beginIt != endIt)
	{
		delete(beginIt->second);
		++beginIt;
	}
	_parameters.clear();
}

void CrMaterial::UploadUniform()
{
	GLuint shaderID = m_pShader->GetShaderID();
	glUseProgram(shaderID);

	std::map<std::string, IMaterialParameter*>::iterator beginIt = _parameters.begin();
	std::map<std::string, IMaterialParameter*>::iterator endIt = _parameters.end();

	while (beginIt != endIt)
	{				 
		GLuint uniformID = glGetUniformLocation(shaderID, beginIt->first.c_str());
		EMaterialParameterType t = beginIt->second->GetType();
		switch (t)
		{
		case eInt:
			glUniform1iv(uniformID, 1, (Int *)beginIt->second->GetPtr());
			break;
		case eFloat:
			glUniform1fv(uniformID, 1, (Float *)beginIt->second->GetPtr());
			break;
		case eFloat2:
			glUniform2fv(uniformID, 1, (Float *)beginIt->second->GetPtr());
			break;
		case eFloat3:
			glUniform3fv(uniformID, 1, (Float *)beginIt->second->GetPtr());
			break;
		case eFloat4:
			glUniform4fv(uniformID, 1, (Float *)beginIt->second->GetPtr());
			break;
		case eTexture:			
		{
			MatTextureParameter* tex = (MatTextureParameter*)(beginIt->second);
			//TODO:						
			glActiveTexture(tex->TexIndex);
			CrTexture * texture = (CrTexture *)beginIt->second->GetPtr();
			glBindTexture(GL_TEXTURE_2D, texture->m_dTextureId);
			glUniform1i(uniformID, tex->Index);
		}
			break;
		default:
			break;
		}
		
		++beginIt;
	}
}

void CrMaterial::SetInt(std::string name, Int value)
{
	MaterialParameter<Int> * v = new MaterialParameter<Int>(std::make_shared<Int>(value));
	v->eType = EMaterialParameterType::eInt;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}

void CrMaterial::SetFloat(std::string name, Float value)
{
	MaterialParameter<Float> * v = new MaterialParameter<Float>(std::make_shared<Float>(value));
	v->eType = EMaterialParameterType::eFloat;
	_parameters.insert(std::make_pair(name, (IMaterialParameter * )v));
}

void CrMaterial::SetVector2(std::string name, Vector2f value)
{
	MaterialParameter<Vector2f> * v = new MaterialParameter<Vector2f>(std::make_shared<Vector2f>(value));
	v->eType = EMaterialParameterType::eFloat2;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}

void CrMaterial::SetVector3(std::string name, Vector3f value)
{
	MaterialParameter<Vector3f> * v = new MaterialParameter<Vector3f>(std::make_shared<Vector3f>(value));
	v->eType = EMaterialParameterType::eFloat3;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}

void CrMaterial::SetVector4(std::string name, Vector4f value)
{
	MaterialParameter<Vector4f> * v = new MaterialParameter<Vector4f>(std::make_shared<Vector4f>(value));
	v->eType = EMaterialParameterType::eFloat4;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}

void CrMaterial::SetColor(std::string name, Vector4f value)
{
	MaterialParameter<Vector4f> * v = new MaterialParameter<Vector4f>(std::make_shared<Vector4f>(value));
	v->eType = EMaterialParameterType::eFloat4;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}

void CrMaterial::SetTexture(std::string name, SharedPtr<CrTexture> value, GLenum e, Int index)
{
	MatTextureParameter * v = new MatTextureParameter(value);
	v->eType = EMaterialParameterType::eTexture;
	v->TexIndex = e;
	v->Index = index;
	_parameters.insert(std::make_pair(name, (IMaterialParameter *)v));
}
