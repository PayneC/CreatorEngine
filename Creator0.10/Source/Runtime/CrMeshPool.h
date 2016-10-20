/*
CreatorEngine
Class CrMeshPool : CrSingleton
Payne
*/

#ifndef _CREATOR_MESHPOOL_H
#define _CREATOR_MESHPOOL_H

#include "CrDefine.h"
#include "CrMeshChunk.h"
#include "CrSingleton.h"
#include <map>

class CrMeshPool
{
	friend class CrEngine;
private:
	CrMeshPool();
	bool Init();
	void Destory();

	CrMeshChunk * CreateMesh(std::string filename);
	CrMeshChunk * CreateFromFbx(const char* filename);
	CrMeshChunk * CreateFromObj(const char* filename);

public:
	~CrMeshPool();

	CrMeshChunk * MeshCube();
	CrMeshChunk * MeshTriangle();

	CrMeshChunk * InsertMesh(std::string name);
	CrMeshChunk * Find(std::string name);
	void Remove(std::string name);
	void RemoveAll();
	void ClearUpCustomMesh();
	void ClearUpDefaultMesh();
	
private:
	std::map<std::string, CrMeshChunk*> m_pMeshs;
	std::map<std::string, CrMeshChunk*>::iterator m_itorMesh;

	CrMeshChunk * m_pMeshCube;
	CrMeshChunk * m_pMeshTriangle;
	//CrMeshChunk * m_pMeshCube;
	//CrMeshChunk * m_pMeshCube;
	//CrMeshChunk * m_pMeshCube;
};


#endif