#include <CrMeshFilter.h>

CrMeshFilter::CrMeshFilter()
{
}

CrMeshFilter::~CrMeshFilter()
{

}

CrMeshFilter * CrMeshFilter::Create(std::string filePath)
{

	return NULL;
}

CrMesh * CrMeshFilter::CreateCube()
{
	CrMesh * date = new CrMesh();

	GLfloat cube_positions[] =
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

	GLushort cube_indices[] =
	{
		0, 1, 2, 3, 6, 7, 4, 5,
		0xffff,
		2, 6, 0, 4, 1, 5, 3, 7,
	};

	date->m_uVertexSize = sizeof(cube_positions);
	date->m_uIndexSize = sizeof(cube_indices);

	glGenBuffers(1, &date->m_uIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, date->m_uIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, date->m_uIndexSize, cube_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &date->m_uVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, date->m_uVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, date->m_uVertexSize, cube_positions, GL_STATIC_DRAW);

	return date;
}
