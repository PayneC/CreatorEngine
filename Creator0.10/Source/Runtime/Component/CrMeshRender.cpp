#include <CrMeshRender.h>
#include <CrGameObject.h>

CrMeshRender::CrMeshRender()
{
}

CrMeshRender::~CrMeshRender()
{

}

void CrMeshRender::Draw(glm::fmat4 & mvp, glm::vec3 & eye, glm::fmat4 & m, glm::fmat4 & v)
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

	glm::vec3 _light(2, 2, 2);

	glUseProgram(shader->GetShaderID());

	GLuint m_uMV = glGetUniformLocation(shader->GetShaderID(), "mModel");
	glUniformMatrix4fv(m_uMV, 1, GL_FALSE, glm::value_ptr(m));

	GLuint m_uMVP = glGetUniformLocation(shader->GetShaderID(), "mModelViewProjection");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

	GLuint m_uBaseColor = glGetUniformLocation(shader->GetShaderID(), "vBaseColor");
	glUniform4fv(m_uBaseColor, 1, glm::value_ptr(material->GetColor()));

	GLuint m_vLightDir = glGetUniformLocation(shader->GetShaderID(), "vLightPos");
	glUniform3fv(m_vLightDir, 1, glm::value_ptr(_light));

	GLuint m_vEyeDir = glGetUniformLocation(shader->GetShaderID(), "vEyePos");
	glUniform3fv(m_vEyeDir, 1, glm::value_ptr(eye));

	glBindVertexArray(m_pMesh->GetVAO());

	CrTexture * texture = material->GetpMainTexture();
	if (texture != NULL)
	{
		GLuint tex0 = glGetUniformLocation(shader->GetShaderID(), "diffuse");		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->m_dTextureId);
		glUniform1i(tex0, 0);
	}

	CrTexture * textureN = material->GetpNormalTexture();
	if (texture != NULL)
	{
		GLuint tex1 = glGetUniformLocation(shader->GetShaderID(), "normal");		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture->m_dTextureId);
		glUniform1i(tex1, 1);
	}

	glDrawElements(GL_TRIANGLES, m_pMesh->GetElementCount(), GL_UNSIGNED_INT, NULL);//GL_TRIANGLE_STRIP

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
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