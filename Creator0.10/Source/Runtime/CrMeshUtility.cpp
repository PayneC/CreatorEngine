#include "CrMeshUtility.h"

#include <string>
#include <fstream>

CrMeshUtility::CrMeshUtility()
{
}

CrMeshUtility::~CrMeshUtility()
{
}

CrMesh *CrMeshUtility::CreateMesh(EPresetMeshType meshType)
{
	switch (meshType)
	{
	case CR_MESH_TYPE_CUBE:
		return CrMeshUtility::Instance()->CreateMeshCube();
	case CR_MESH_TYPE_QUAD:
		return CrMeshUtility::Instance()->CreateMeshQuad();
	default:
		return NULL;
	}
}

CrMesh *CrMeshUtility::CreateMeshCube()
{
	if (m_BuiltinMeshs[CR_MESH_TYPE_CUBE] != NULL)
		return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE] = new CrMesh();

	GLfloat vertices[] =
	{
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		-0.5,0.5,0.5,
		0.5,0.5,0.5,

		-0.5,0.5,-0.5,
		0.5,0.5,-0.5,
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,

		-0.5,0.5,0.5,
		0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		0.5,0.5,-0.5,

		-0.5,-0.5,-0.5,
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		0.5,-0.5,-0.5,

		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		0.5,0.5,-0.5,
		0.5,-0.5,-0.5,
		
		-0.5,-0.5,-0.5,
		-0.5,0.5,-0.5,
		-0.5,0.5,0.5,
		-0.5,-0.5,0.5,
	};

	GLfloat normals[] =
	{
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
		0,1,0,
		0,1,0,
		0,0,-1,
		0,0,-1,
		0,1,0,
		0,1,0,
		0,0,-1,
		0,0,-1,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
	};
	GLfloat tangents[] =
	{
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		0,0,-1,
		0,0,-1,
		0,0,-1,
		0,0,-1,
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,		
	};

	GLfloat uvs[] =
	{
		0,0,
		1,0,
	0,1,
	1,1,
	0,1,
	1,1,
	0,1,
	1,1,
	0,0,
	1,0,
	0,0,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	};

	GLushort triangles[] =
	{
		2,3,0,
		1,3,2,
		5,4,8,
		9,5,8,
		7,6,10,
		11,7,10,
		14,13,12,
		15,14,12,
		18,17,16,
		19,18,16,
		22,21,20,
		23,22,20,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	size_t verticeSize = sizeof(vertices);
	size_t normalSize = sizeof(normals);
	size_t tangentSize = sizeof(tangents);
	size_t uvSize = sizeof(uvs);

	size_t triangleSize = sizeof(triangles);

	//�������㻺�����
	//VertexBufferObject
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticeSize + normalSize + tangentSize + uvSize, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeSize, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize, normalSize, normals);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize + normalSize, tangentSize, triangles);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize + normalSize + tangentSize, uvSize, uvs);

	//������������
	//ElementBufferObject
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleSize, triangles, GL_STATIC_DRAW);

	//���������������
	//VertexArrayObject
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//���ö�������(���������ڶ��㻺�棩
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		0,		  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
		);

	glEnableVertexAttribArray(1); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		1,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void *)verticeSize // array buffer offset
		);

	glEnableVertexAttribArray(3); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		3,								   // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,								   // size
		GL_FLOAT,						   // type
		GL_FALSE,						   // normalized?
		0,								   // stride
		(void *)(verticeSize + normalSize) // array buffer offset
		);

	glEnableVertexAttribArray(2); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		2,												 // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,												 // size
		GL_FLOAT,										 // type
		GL_FALSE,										 // normalized?
		0,												 // stride
		(void *)(verticeSize + normalSize + tangentSize) // array buffer offset
		);

	//��������(�����������������棩
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindVertexArray(0);

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetVAO(VAO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetVBO(VBO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetEBO(EBO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetElementCount(triangleSize);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetName("cube");

	return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];
}

CrMesh *CrMeshUtility::CreateMeshQuad()
{
	if (m_BuiltinMeshs[CR_MESH_TYPE_QUAD] != NULL)
		return m_BuiltinMeshs[CR_MESH_TYPE_QUAD];

	m_BuiltinMeshs[CR_MESH_TYPE_QUAD] = new CrMesh();

	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	GLfloat normals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	GLfloat uvs[] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	GLushort triangles[] =
	{
		0, 1, 3,
		0, 3, 2,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	size_t verticeSize = sizeof(vertices);
	size_t normalSize = sizeof(normals);
	size_t uvSize = sizeof(uvs);

	size_t triangleSize = sizeof(triangles);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticeSize + normalSize + uvSize, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeSize, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize, normalSize, normals);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize + normalSize, uvSize, uvs);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleSize, triangles, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		0,		  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
		);

	glEnableVertexAttribArray(1); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		1,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void *)verticeSize // array buffer offset
		);

	glEnableVertexAttribArray(2); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		2,								   // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,								   // size
		GL_FLOAT,						   // type
		GL_FALSE,						   // normalized?
		0,								   // stride
		(void *)(verticeSize + normalSize) // array buffer offset
		);

	glBindVertexArray(0);

	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetVAO(VAO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetVBO(VBO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetEBO(EBO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetElementCount(triangleSize);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetName("cube");

	return m_BuiltinMeshs[CR_MESH_TYPE_QUAD];
}