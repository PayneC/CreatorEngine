#include <CrMaterial.h>

CrMaterial * CrMaterial::CreateCrMaterial()
{
	CrMaterial * _instance = new CrMaterial();//CrObject::Instance<CrGameObject>();
	return _instance;
}

CrMaterial::CrMaterial()
	:m_pShader(0)
	, m_dColor(1.f)
	, m_pMainTextur(NULL)
	, m_v2mainTextureOffset(0.f)
	, m_v2mainTextureScale(0.f)
{
}

CrMaterial::~CrMaterial()
{

}

void CrMaterial::UploadUniform()
{

}

void CrMaterial::SetColor(glm::vec4 & color)
{
	m_dColor = color;
}