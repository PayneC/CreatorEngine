#include "CrModel.h"
#include "CrEngine.h"

CrModel::CrModel()
{
}

CrModel::~CrModel()
{
}

CrMeshChunk * CrModel::GetMesh()
{
	return m_pMesh; 
}

void CrModel::SetMesh(CrMeshChunk * var)
{
	if (!var) return;
	if (m_pMesh)
		m_pMesh->Release();

	m_pMesh = var;
	m_pMesh->Retain();
}

CrModel * CrModel::CreateCube()
{
	CrModel * pModel = new CrModel();
	if (pModel && pModel->InitCube())
	{
		return pModel;
	}
	CR_SAFE_DELETE(pModel);
	return NULL;
}
CrModel * CrModel::CreateTriangle()
{
	CrModel * pModel = new CrModel();
	if (pModel && pModel->InitTriangle())
	{
		return pModel;
	}
	CR_SAFE_DELETE(pModel);
	return NULL;
}
bool CrModel::InitCube()
{
	m_pMesh = CrEngine::MeshPool()->MeshCube();
	if (m_pMesh)
	{
		SetType(CrEModelType::MT_CUBE);
		m_pMesh->Retain();
		return true;
	}
	return false;
}
bool CrModel::InitTriangle()
{
	m_pMesh = CrEngine::MeshPool()->MeshTriangle();
	if (m_pMesh)
	{
		SetType(CrEModelType::MT_TRIANGLE);
		m_pMesh->Retain();
		return true;
	}
	return false;
}
void CrModel::Destroy()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
	}
}
void CrModel::Render()
{
	CrGameObject::Render();
	if (!m_isActive)
		return;
	CrEngine::Director()->AddDrawTarget(this);

	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)m_pMesh->m_dVertexSize);
	glEnableVertexAttribArray(1);

	//index-着色器中的位置
	//glVertexAttribPointer(m_pIndices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(m_pIndices);

	//m_iProjectionIdU = glGetUniformLocation(m_program, "ProjectionMatrix");
	//m_iViewIdU = glGetUniformLocation(m_program, "ViewMatrix");
	//m_iCrdelIdU = glGetUniformLocation(m_program, "ModelMatrix");
	//m_iAnchorPoint = glGetUniformLocation(m_program, "AnchorPoint");

	////投影矩阵
	//glm::mat4 projection = glm::perspective(45.f, 4.f / 3.f, 1.f, 100.f);
	//glUniformMatrix4fv(m_iProjectionIdU, 1, GL_FALSE, &projection[0][0]);

	//m_vc4AnchorPoint.x = 1.f;
	//m_vc4AnchorPoint.y = 1.f;
	//m_vc4AnchorPoint.z = 0.f;
	//m_vc4AnchorPoint.w = 0.f;
	//glUniform4fv(m_iAnchorPoint, 1, &m_vc4AnchorPoint[0]);
	////视图矩阵
	//glm::mat4 view = glm::lookAt(glm::vec3(-5.f, 4.f, -15.f), glm::vec3(-5.f, 4.f, -1.f), glm::vec3(0, 1, 0));
	//glUniformMatrix4fv(m_iViewIdU, 1, GL_FALSE, &view[0][0]);

	//glm::mat4 Modle(1.0f);
	//glUniformMatrix4fv(m_iModelIdU, 1, GL_FALSE, &Modle[0][0]);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//点大小
	glPointSize(1.f);
	//线宽
	glLineWidth(1.f);
	//正反面
	glFrontFace(GL_CCW);
	//裁剪
	glCullFace(GL_BACK);
	//开启
	glEnable(GL_CULL_FACE);
	//渲染模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawArrays(GL_TRIANGLES, 0, 3102);
	glDrawElements(GL_TRIANGLES, m_pMesh->m_dElementSize, GL_UNSIGNED_SHORT, 0);
	*/
}
