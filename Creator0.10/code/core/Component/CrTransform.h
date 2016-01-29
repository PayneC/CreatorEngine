/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_TRANSFORM_H
#define _CREATOR_TRANSFORM_H

#include "CrDefine.h"
#include "CrComponent.h"

class CrTransform : public CrComponent
{
	enum ETransformDirtyFlag : uint64_t
	{
		TDF_NONE = 0,
		TDF_GP = 1 << 0,
		TDF_GR = 1 << 1,
		TDF_GS = 1 << 2,
		TDF_LP = 1 << 3,
		TDF_LR = 1 << 4,
		TDF_LS = 1 << 5,
	};

public:
	CrTransform();
	~CrTransform();

	FuncGetSet(glm::vec3, Postion);
	FuncGetSet(glm::vec3, Rotation);
	FuncGetSet(glm::vec3, Scale);
	FuncGetSet(glm::vec3, LocalPostion);
	FuncGetSet(glm::vec3, LocalRotation);
	FuncGetSet(glm::vec3, LocalScale);
	EasyGetFuncOnly(glm::vec3, m_v3Forword, Forword);
	EasyGetFuncOnly(glm::vec3, m_v3Left, Left);
	EasyGetFuncOnly(glm::vec3, m_v3Up, Up);

	EasyGetFuncOnly(glm::mat4, m_m4LocalToWorld, LocalToWorldMatrix);
	EasyGetFuncOnly(glm::mat4, m_m4WorldToLocal, WorldToLocalMatrix);

// 	void Awake();
// 	void OnEnable();
// 	void OnDisable();
// 	void Update(float dt);
// 	void LateUpdate(float dt);
// 	void FixedUpdate(float dt);
// 	void Destroy();

	glm::quat GetQuaternion();

private:
	void _AddDirtyFlag(uint64_t flag);
	void _RemoveDirtyFlag(uint64_t flag);
	bool _CheckDirtyFlag(uint64_t flag);
	void _ExecuteTranslate();
	void _ExecutePostion();
	void _ExecuteRotation();
	void _ExecuteScale();
	void _ExecuteMatrix();
private:
	
	glm::vec3 m_v3Postion;
	glm::vec3 m_v3Rotation;
	glm::vec3 m_v3Scale;
	
	glm::vec3 m_v3LocalPostion;
	glm::vec3 m_v3LocalRotation;
	glm::vec3 m_v3LocalScale;

	uint64_t m_uDirtyFlags;

	
};

#endif