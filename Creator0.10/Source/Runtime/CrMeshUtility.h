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

class DLL_ClASS CrMeshUtility : public CrSingleton<CrMeshUtility>
{
public:
	CrMeshUtility();
	~CrMeshUtility();

	static CrMesh* CreateMesh(EPresetMeshType meshType);
	static CrMesh* CreateMesh(const char* filename);
private:
	CrMesh* CreateMeshCube();
	CrMesh* CreateMeshQuad();
	CrMesh* m_BuiltinMeshs[CR_MESH_TYPE_COUNT];
};

#endif