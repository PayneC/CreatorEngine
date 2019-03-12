#include <CrMeshRender.h>
#include <CrGameObject.h>

CrMeshRender::CrMeshRender()
{
}

CrMeshRender::~CrMeshRender()
{

}

void CrMeshRender::Draw(glm::fmat4 & p, glm::vec3 & eye, glm::fmat4 & m, glm::fmat4 & v)
{
	if (m_pMaterials.empty())
	{
		return;
	}

	SharedPtr<CrMaterial> material = m_pMaterials[0];
	if (material == NULL)
	{
		return;
	}

	SharedPtr<CrShader> shader = material->GetShader();
	if (shader == NULL)
	{
		return;
	}

	glm::vec3 _light(2, 2, 2);

	if (GetGameObject()->get_name() == "skybox")
	{
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
	}	

	glUseProgram(shader->GetShaderID());
	
	glBindVertexArray(m_pMesh->GetVAO());

	GLuint m_Model = glGetUniformLocation(shader->GetShaderID(), "mModel");
	glUniformMatrix4fv(m_Model, 1, GL_FALSE, glm::value_ptr(m));	

	if (GetGameObject()->get_name() == "skybox")
	{
		GLuint m_View = glGetUniformLocation(shader->GetShaderID(), "mView");
		glm::mat4 v2 = glm::mat4(glm::mat3(v));
		glUniformMatrix4fv(m_View, 1, GL_FALSE, glm::value_ptr(v2));
	}
	else
	{
		GLuint m_View = glGetUniformLocation(shader->GetShaderID(), "mView");
		glUniformMatrix4fv(m_View, 1, GL_FALSE, glm::value_ptr(v));
	}	

	GLuint m_Projection = glGetUniformLocation(shader->GetShaderID(), "mProjection");
	glUniformMatrix4fv(m_Projection, 1, GL_FALSE, glm::value_ptr(p));

	GLuint m_uMVP = glGetUniformLocation(shader->GetShaderID(), "mModelViewProjection");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(p * v * m));

	GLuint vLightPos = glGetUniformLocation(shader->GetShaderID(), "vLightPos");
	glUniform3fv(vLightPos, 1, glm::value_ptr(eye));

	GLuint vEyePos = glGetUniformLocation(shader->GetShaderID(), "vEyePos");
	glUniform3fv(vEyePos, 1, glm::value_ptr(eye));

	material->UploadUniform();

	glDrawElements(GL_TRIANGLES, m_pMesh->GetElementCount(), GL_UNSIGNED_INT, NULL);//GL_TRIANGLE_STRIP

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	if (GetGameObject()->get_name() == "skybox")
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
	}
	glUseProgram(0);
}

void CrMeshRender::SetMaterial(SharedPtr<CrMaterial> material)
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

SharedPtr<CrMaterial> CrMeshRender::GetMaterial()
{
	if (!m_pMaterials.empty())
	{
		return m_pMaterials[0];
	}
	return NULL;
}

void CrMeshRender::SetMesh(SharedPtr<CrMesh> mesh)
{
	m_pMesh = mesh;
}

SharedPtr<CrMesh> CrMeshRender::GetMesh()
{
	return m_pMesh;
}