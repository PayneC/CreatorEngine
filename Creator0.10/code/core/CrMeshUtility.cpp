#include "CrMeshUtility.h"


#include <string>
#include <fstream>

CrMeshUtility::CrMeshUtility()
{
}

CrMeshUtility::~CrMeshUtility()
{
}

CrMesh* CrMeshUtility::CreateMesh(EPresetMeshType meshType)
{
	switch (meshType)
	{
	case CR_MESH_TYPE_CUBE:
		return CrMeshUtility::Instance()->CreateMeshCube();
	default:
		return NULL;
	}
}

CrMesh* CrMeshUtility::CreateMeshCube()
{
	if (m_BuiltinMeshs[CR_MESH_TYPE_CUBE] != NULL)
		return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE] = new CrMesh();

	GLuint vertexId = 0;

	GLuint buffIds[4];

	size_t positionSize = 0;
	size_t normalSize = 0;
	size_t UVSize = 0;
	size_t elementSize = 0;

	GLfloat positions[] =
	{
		-0.5f, -0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
	};
	positionSize = sizeof(positions);

	GLushort elements[] =
	{
		0, 1, 2, 3, 6, 7, 4, 5,
		0xffff,
		2, 6, 0, 4, 1, 5, 3, 7,
	};
	elementSize = sizeof(elements);

	glGenBuffers(4, buffIds);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffIds[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elements, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffIds[0]);
	glBufferData(GL_ARRAY_BUFFER, positionSize, positions, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexId);
	glBindVertexArray(vertexId);

	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	//glEnableVertexAttribArray(1); //attribute 1. No particular reason for 1, but must match the layout in the shader.

	glBindBuffer(GL_ARRAY_BUFFER, buffIds[0]);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0			// array buffer offset
		);

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetPositionBufferID(buffIds[0]);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetNormalBufferID(buffIds[1]);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetUVBufferID(buffIds[2]);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetElementBufferID(buffIds[3]);

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetPositionSize(positionSize);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetNormalSize(normalSize);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetUVSize(UVSize);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetElementSize(elementSize);

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetName("cube");

	return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];
}
