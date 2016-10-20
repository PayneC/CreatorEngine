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

	glUseProgram(shader->GetShaderID());

	GLuint m_uMVP = glGetUniformLocation(shader->GetShaderID(), "MVP");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

	GLuint m_uBaseColor = glGetUniformLocation(shader->GetShaderID(), "BaseColor");
	glUniform4fv(m_uBaseColor, 1, glm::value_ptr(material->GetColor()));
	
	glBindVertexArray(m_pMesh->GetVAO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMesh->GetEBO());

	CrTexture * texture = material->GetpMainTexture();
	if (texture != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture->m_dTextureId);
	}


	glDrawElements(GL_TRIANGLES, m_pMesh->GetElementCount() / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);//GL_TRIANGLE_STRIP
	
	glBindVertexArray(0);
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