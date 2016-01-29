/*
CreatorEngine
Class CrMeshRender : CrComponent
Payne
*/

#ifndef _CREATOR_MESHRENDER_H
#define _CREATOR_MESHRENDER_H

#include <CrDefine.h>
#include <CrComponent.h>
#include <string>
#include <CrMesh.h>
#include <CrMaterial.h>

class CrMeshRender : public CrComponent
{
public:
	CrMeshRender();
	~CrMeshRender();

public:


protected:
	CrMesh * m_pMesh;
	CrMaterial * m_pMaterial;
};


#endif