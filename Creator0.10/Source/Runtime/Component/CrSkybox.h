/*
CreatorEngine
Class CrSkybox : CrComponent
Payne
*/

#ifndef _CREATOR_SKYBOX_H
#define _CREATOR_SKYBOX_H

#include <CrDefine.h>
#include <string>
#include <vector>
#include <Component\CrMesh.h>
#include <Component\CrMaterial.h>

class DLL_ClASS CrSkybox : public CrComponent
{
public:
	CrSkybox();
	~CrSkybox();

public:
	void Draw(glm::fmat4 & mvp);	
	EasyGetSet(CrMesh*, m_pMesh, Mesh);
	EasyGetSet(CrMaterial*, m_pMaterial, Material);
};


#endif