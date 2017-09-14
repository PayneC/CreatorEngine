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

	// ���ö�������ָ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// ���÷���ָ��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	// ���ö������������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

	m_uElementCount = this->indices.size();
}