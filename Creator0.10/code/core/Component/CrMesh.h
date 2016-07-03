/*
CreatorEngine
Class CrMesh : CrObject
Payne
*/

#ifndef _CREATOR_MESH_H
#define _CREATOR_MESH_H

#include <CrDefine.h>
#include <CrComponent.h>
#include <string>
#include <CrObject.h>

class CrMesh : public CrObject
{
	friend class CrMeshUtility;
public:
	CrMesh();
	~CrMesh();

public:
	EasyGetSet(std::string, m_sName, Name);
	
	EasyGetSet(GLuint, m_uVertexId, VertexID);

	EasyGetSet(GLuint, m_uPositionBufferId, PositionBufferID);
	EasyGetSet(GLuint, m_dElementBufferId, ElementBufferID);
	EasyGetSet(GLuint, m_dNormalBufferId, NormalBufferID);
	EasyGetSet(GLuint, m_dUVBufferId, UVBufferID);

	EasyGetSet(size_t, m_uPositionSize, PositionSize);
	EasyGetSet(size_t, m_uElementSize, ElementSize);
	EasyGetSet(size_t, m_dNormalSize, NormalSize);
	EasyGetSet(size_t, m_dUVSize, UVSize);
private:
	

};


#endif