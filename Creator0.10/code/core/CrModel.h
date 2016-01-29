/*
CreatorEngine
Class CrModel : CrNode
Payne
*/

#ifndef _CREATOR_MODEL_H
#define _CREATOR_MODEL_H

#include "CrGameObject.h"

#include "CrMeshPool.h"

enum CrEModelType
{
	MT_CUSTOM	= 0,
	MT_CUBE		= 1,	//立方体.
	MT_SPHERE	= 2,	//球体.
	MT_CAPSULE	= 3,	//胶囊体.
	MT_CYLINDER = 4,	//圆柱体.
	MT_PLANE	= 5,	//平面.
	MT_QUAD		= 6,	//四边形.
	MT_TRIANGLE = 7,	//三角形.
};


class CrModel : public CrGameObject
{
	friend class CrRender;
public:
	static CrModel * CreateCube();
	static CrModel * CreateTriangle();
public:
	CrModel();
	~CrModel();

	void Render();
	bool InitCube(); 
	bool InitTriangle();
	virtual void Destroy();
	EasyGetSetFuncOnly(CrMeshChunk*, m_pMesh, Mesh);
	EasyGetSet(CrEModelType, m_eType, Type);
	EasyGetSet(GLuint, m_uUseShader, Shader);
private:
	
};

#endif