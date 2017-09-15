/*
CreatorEngine
Class CrMeshUtility
Payne
*/

#ifndef _CREATOR_MESHUTILITY_H
#define _CREATOR_MESHUTILITY_H

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <Component\CrMesh.h>
#include "CrDefine.h"
#include "CrSingleton.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CrGameObject.h"

class DLL_ClASS CrMeshUtility : public CrSingleton<CrMeshUtility>
{
public:
	CrMeshUtility();
	~CrMeshUtility();

	static CrMesh* CreateMesh(EPresetMeshType meshType);
	static CrGameObject* LoadModel(const char* filename);
	static CrGameObject* processNode(aiNode *node, const aiScene *scene);
	static CrGameObject* processMesh(aiMesh *mesh, const aiScene *scene);
private:
	CrMesh* CreateMeshCube();
	CrMesh* CreateMeshQuad();
	CrMesh* m_BuiltinMeshs[CR_MESH_TYPE_COUNT];
};

#endif