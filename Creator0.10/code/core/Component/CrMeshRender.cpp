#include <CrMeshRender.h>
#include <CrGameObject.h>

CrMeshRender::CrMeshRender()
{
}

CrMeshRender::~CrMeshRender()
{

}

void CrMeshRender::Draw(glm::fmat4 & mvp)
{
	if (m_pMaterials.empty())
	{
		return;
	}

	CrMaterial * material = m_pMaterials[0];
	if (material == NULL)
	{
		return;
	}

	CrShader * shader = material->GetShader();
	if (shader == NULL)
	{
		return;
	}

	shader->UseShader();

	GLuint m_uMVP = glGetUniformLocation(shader->GetShaderID(), "MVP");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

	GLuint m_uBaseColor = glGetUniformLocation(shader->GetShaderID(), "BaseColor");
	glUniform4fv(m_uBaseColor, 1, glm::value_ptr(material->GetColor()));
	
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xffff);

	glBindVertexArray(m_pMesh->GetVertexID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMesh->GetElementBufferID());
	glDrawElements(GL_TRIANGLE_STRIP, m_pMesh->GetElementSize() / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);//GL_TRIANGLE_STRIP
}

void CrMeshRender::SetMaterial(CrMaterial * material)
{
	if (m_pMaterials.empty())
	{
		m_pMaterials.push_back(material);
	}
	else
	{
		m_pMaterials[0] = material;
	}
}

CrMaterial * CrMeshRender::GetMaterial()
{
	if (!m_pMaterials.empty())
	{
		return m_pMaterials[0];
	}
	return NULL;
}