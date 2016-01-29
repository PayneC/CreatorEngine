#include "CrRender.h"

CrRender::CrRender()
: m_m4Projection(1.f)
, m_m4View(1.f)
, m_m4MVP(1.f)
, m_m4Model(1.f)
{
	m_m4Projection = glm::perspective(45.f, 16.f / 9.f, 0.1f, 100.f);
}

CrRender::~CrRender()
{
}

void CrRender::SetProjectionMatrix(glm::fmat4 *pfmat4)
{
	m_m4Projection = *pfmat4;
}

void CrRender::SetViewMatrix(glm::fmat4 *pfmat4)
{
	m_m4View = *pfmat4;
}

void CrRender::DrawTriangle(CrModel * pModel)
{
	if (pModel->m_uUseShader != m_uCurrentShader)
	{
		m_uCurrentShader = pModel->m_uUseShader;
		glUseProgram(m_uCurrentShader);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pModel->GetMesh()->GetVertexBufferId());
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
}
void CrRender::DrawCube(CrModel * pModel)
{
	if (pModel->m_uUseShader != m_uCurrentShader)
	{
		m_uCurrentShader = pModel->m_uUseShader;
		glUseProgram(m_uCurrentShader);
	}

	m_m4Model = pModel->m_m4Transform * pModel->m_m4AnchorOffset;
	m_m4MVP = m_m4Projection * m_m4View * m_m4Model;

	m_uMVP = glGetUniformLocation(m_uCurrentShader, "MVP");
	glUniformMatrix4fv(m_uMVP, 1, GL_FALSE, glm::value_ptr(m_m4MVP));

	glBindBuffer(GL_ARRAY_BUFFER, pModel->GetMesh()->GetVertexBufferId());

	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glEnableVertexAttribArray(1); //attribute 1. No particular reason for 1, but must match the layout in the shader.
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0			// array buffer offset
		);
	glVertexAttribPointer(
		1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_TRUE,           // normalized?
		0,                  // stride
		(GLvoid*)pModel->GetMesh()->GetVertexSize()			// array buffer offset
		);
	
	glBindVertexArray(pModel->GetMesh()->GetVertexBufferId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pModel->GetMesh()->GetElementBufferId());

	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xffff);

	glDrawElements(GL_TRIANGLE_STRIP, pModel->GetMesh()->GetElementSize() / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);//GL_TRIANGLE_STRIP
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void CrRender::Draw(CrModel * pModel)
{
	switch (pModel->GetType())
	{
	case MT_CUSTOM:	
		break;
	case MT_CUBE:
		DrawCube(pModel);
		break;
	case MT_SPHERE:
		break;
	case MT_CAPSULE:
		break;
	case MT_CYLINDER:
		break;
	case MT_PLANE:
		break;
	case MT_QUAD:
		break;
	case MT_TRIANGLE:
		break;
	default:
		break;
	}
}

bool CrRender::Init()
{

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

	return true;
}