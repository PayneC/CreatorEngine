#include <CrMesh.h>

CrMesh::CrMesh()
{
}

CrMesh::~CrMesh()
{

}

void CrMesh::SetupMesh()
{
	glGenVertexArrays(1, &this->m_uVAO);
	glGenBuffers(1, &this->m_uVBO);
	glGenBuffers(1, &this->m_uEBO);

	glBindVertexArray(this->m_uVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_uVBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_uEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// 设置顶点坐标指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// 设置法线指针
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	// 设置顶点的纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

	m_uElementCount = this->indices.size();
}