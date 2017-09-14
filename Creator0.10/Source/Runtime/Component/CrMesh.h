/*
CreatorEngine
Class CrMesh : CrObject
Payne
*/

#ifndef _CREATOR_MESH_H
#define _CREATOR_MESH_H

#include <CrDefine.h>
#include <Component\CrComponent.h>
#include <string>
#include <CrObject.h>

#include <vector>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

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
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


#endif