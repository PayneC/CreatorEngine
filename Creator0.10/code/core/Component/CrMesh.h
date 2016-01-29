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
	friend class CrMeshFilter;
public:
	CrMesh();
	~CrMesh();

public:
	EasyGet(std::string, m_sName, Name);
	
	EasyGet(GLuint, m_uVertexBufferId, VertexBufferID);
	EasyGet(GLuint, m_uIndexBufferId, IndexBufferID);
	EasyGet(size_t, m_uVertexSize, VertexSize);
	EasyGet(size_t, m_uIndexSize, IndexSize);
private:
	

};


#endif