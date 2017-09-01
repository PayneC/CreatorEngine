/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_TRANSFORM_H
#define _CREATOR_TRANSFORM_H

#include "CrDefine.h"
#include "CrComponent.h"
#include <vector>

class CrTransform : public CrComponent
{
	friend class CrGameObject;
public:
	CrTransform();
	~CrTransform();

	EasyGet(CrTransform *, m_pParent, Parent);		

	FuncGetSet(glm::vec3, Position);
	FuncGetSet(glm::vec3, Rotation);
	FuncGetSet(glm::vec3, LocalPosition);
	FuncGetSet(glm::vec3, LocalRotation);
	FuncGetSet(glm::vec3, LocalScale);
	EasyGetFuncOnly(glm::vec3, m_v3Forword, Forword);
	EasyGetFuncOnly(glm::vec3, m_v3Right, Right);
	EasyGetFuncOnly(glm::vec3, m_v3Up, Up);

	EasyGetFuncOnly(glm::mat4, m_m4LocalToWorld, LocalToWorldMatrix);
	EasyGetFuncOnly(glm::mat4, m_m4WorldToLocal, WorldToLocalMatrix);

	EasyGetFuncOnly(glm::quat, m_qQuaternion, Quaternion);

	void LookAt(CrGameObject * gameobject);
	void LookAt(CrTransform * transform);
	void LookAt(glm::vec3 position);

	glm::vec3 GetScale();

	void SetChildrenPositionDirty();
	void SetChildrenRotationDirty();
	void SetChildrenScaleDirty();
private:
	void _ExecuteMatrix();
	void AddChild(CrTransform * pChild);
	void RemoveChild(CrTransform * pChild);
	void RemoveAllChild();
private:
	
	glm::vec3 m_v3Position;
	glm::vec3 m_v3Rotation;
	glm::vec3 m_v3Scale;
	
	glm::vec3 m_v3LocalPosition;
	glm::vec3 m_v3LocalRotation;
	glm::vec3 m_v3LocalScale;

	bool m_isPositionDirty;
	bool m_isRotationDirty;
	bool m_isScaleDirty;
	bool m_isDirty;

	glm::vec3 m_xAxis;
	glm::vec3 m_yAxis;
	glm::vec3 m_zAxis;

	std::vector<CrTransform *> m_pChildren;
};

#endif