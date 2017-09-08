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
	void Draw(glm::fmat4 & mvp, glm::vec3 & eye, glm::fmat4 & mv, glm::fmat4 & v);
	EasyGetSet(CrMesh*, m_pMesh, Mesh);
	EasyGetSet(int8_t, m_CastShadows, CastShadows);				   //Ͷ��Ӱ��
	EasyGetSet(int8_t, m_ReceiveShadows, ReceiveShadows);		   //����Ӱ��
	EasyGetSet(int8_t, m_UseLightProbes, UseLightProbes);		   //�ƹ�̽����
	EasyGetSet(int8_t, m_ReflectionProbes, ReflectionProbes);	   //����̽ͷ

	void SetMaterial(CrMaterial * material);
	CrMaterial * GetMaterial();

protected:
	std::vector<CrMaterial *> m_pMaterials;
};


#endif