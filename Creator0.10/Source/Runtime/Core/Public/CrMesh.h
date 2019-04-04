/*
CreatorEngine
Class CrMesh : CrObject
Payne
*/

#ifndef _CREATOR_MESH_H
#define _CREATOR_MESH_H

#include <CrObject.h>

class DLL_ClASS CrMesh : public CrObject
{
	friend class CrMeshUtility;
public:
	CrMesh();
	~CrMesh();

public:
	EasyGetSet(std::string, m_sName, Name);
	
	EasyGetSet(GLuint, m_uVAO, VAO);
	EasyGetSet(GLuint, m_uVBO, VBO);
	EasyGetSet(GLuint, m_uEBO, EBO);
	EasyGetSet(GLuint, m_uElementCount, ElementCount);

	void SetupMesh();
	void UploadVextex();
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


#endif