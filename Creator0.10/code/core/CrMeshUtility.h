/*
CreatorEngine
Class CrMeshUtility
Payne
*/

#ifndef _CREATOR_MESHUTILITY_H
#define _CREATOR_MESHUTILITY_H

#include <glew\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "CrMesh.h"
#include "CrDefine.h"
#include "CrSingleton.h"

class CrMeshUtility : public CrSingleton<CrMeshUtility>
{
public:
	CrMeshUtility();
	~CrMeshUtility();

	static CrMesh* CreateMesh(EPresetMeshType meshType);
private:
	CrMesh* CreateMeshCube();
	CrMesh* m_BuiltinMeshs[CR_MESH_TYPE_COUNT];
};

#endif