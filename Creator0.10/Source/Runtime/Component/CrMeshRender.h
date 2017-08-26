/*
CreatorEngine
Class CrMeshRender : CrComponent
Payne
*/

#ifndef _CREATOR_MESHRENDER_H
#define _CREATOR_MESHRENDER_H

#include <CrDefine.h>
#include <string>
#include <vector>
#include <Component\CrMesh.h>
#include <Component\CrMaterial.h>

class CrMeshRender : public CrComponent
{
public:
	CrMeshRender();
	~CrMeshRender();

public:
	void Draw(glm::fmat4 & mvp);	
	EasyGetSet(CrMesh*, m_pMesh, Mesh);
	EasyGetSet(int8_t, m_CastShadows, CastShadows);				   //投射影子
	EasyGetSet(int8_t, m_ReceiveShadows, ReceiveShadows);		   //接收影子
	EasyGetSet(int8_t, m_UseLightProbes, UseLightProbes);		   //灯光探测器
	EasyGetSet(int8_t, m_ReflectionProbes, ReflectionProbes);	   //反射探头

	void SetMaterial(CrMaterial * material);
	CrMaterial * GetMaterial();

protected:
	std::vector<CrMaterial *> m_pMaterials;
};


#endif