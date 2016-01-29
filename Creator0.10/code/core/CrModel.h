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
	MT_CUBE		= 1,	//������.
	MT_SPHERE	= 2,	//����.
	MT_CAPSULE	= 3,	//������.
	MT_CYLINDER = 4,	//Բ����.
	MT_PLANE	= 5,	//ƽ��.
	MT_QUAD		= 6,	//�ı���.
	MT_TRIANGLE = 7,	//������.
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