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
#include <CrMesh.h>
#include "CrDefine.h"
#include "CrSingleton.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <CrGameObject.h>

class DLL_ClASS CrMeshUtility : public CrSingleton<CrMeshUtility>
{
public:
	CrMeshUtility();
	~CrMeshUtility();

	static std::shared_ptr<CrMesh>  CreateMesh(EPresetMeshType meshType);
	static std::shared_ptr<CrGameObject>  LoadModel(const char* filename);
	static std::shared_ptr<CrGameObject>  processNode(aiNode *node, const aiScene *scene);
	static std::shared_ptr<CrGameObject>  processMesh(aiMesh *mesh, const aiScene *scene);
private:
	std::shared_ptr<CrMesh>  CreateMeshCube();
	std::shared_ptr<CrMesh>  CreateMeshQuad();
	std::shared_ptr<CrMesh>  m_BuiltinMeshs[CR_MESH_TYPE_COUNT];
};

#endif