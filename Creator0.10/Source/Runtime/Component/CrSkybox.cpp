#include <CrSkybox.h>
#include <CrGameObject.h>

CrSkybox::CrSkybox()
{
}

CrSkybox::~CrSkybox()
{

}

void CrSkybox::Draw(glm::fmat4 & mvp)
{
	if (!m_pMaterial)
	{
		return;
	}

	CrMaterial * material = m_pMaterial;
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

	GLuint m_uMVP = glGetUniformLocation(shader->GetShaderID(), "mModelViewMatrix");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));

	GLuint m_uBaseColor = glGetUniformLocation(shader->GetShaderID(), "vBaseColor");
	glUniform4fv(m_uBaseColor, 1, glm::value_ptr(material->GetColor()));

	GLuint m_vLightDir = glGetUniformLocation(shader->GetShaderID(), "vLightDir");
	glUniform3fv(m_vLightDir, 1, glm::value_ptr(glm::vec3(0, 0, 1)));
	
	glBindVertexArray(m_pMesh->GetVAO());	

	CrTexture * texture = material->GetpMainTexture();
	if (texture != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture->m_dTextureId);
	}

	glDrawElements(GL_TRIANGLES, m_pMesh->GetElementCount() / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);//GL_TRIANGLE_STRIP
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}