/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_TRANSFORM_H
#define _CREATOR_TRANSFORM_H

#include <CrComponent.h>

class DLL_ClASS CrTransform : public CrComponent, public std::enable_shared_from_this<CrTransform>
{
	friend class CrGameObject;
public:
	CrTransform();
	~CrTransform();

	std::shared_ptr<CrTransform> GetParent();
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

	void LookAt(std::shared_ptr<CrGameObject> gameobject);
	void LookAt(std::shared_ptr<CrTransform> transform);
	void LookAt(glm::vec3 position);

	glm::vec3 GetScale();

	void SetChildrenPositionDirty();
	void SetChildrenRotationDirty();
	void SetChildrenScaleDirty();
	void SetParent(std::shared_ptr<CrTransform> pParent);
	std::vector<std::shared_ptr<CrTransform>> get_children() { return m_pChildren; }
private:
	void _ExecuteMatrix();
	
	void RemoveChild(std::shared_ptr<CrTransform> pChild);
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

	std::vector<std::shared_ptr<CrTransform>> m_pChildren;
	std::weak_ptr<CrTransform> m_pParent;
};
#endif