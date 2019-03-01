/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_TRANSFORM_H
#define _CREATOR_TRANSFORM_H

#include <CrComponent.h>

class DLL_ClASS CrTransform : public CrComponent, public EnableSharedFromThis<CrTransform>
{
	friend class CrGameObject;
public:
	CrTransform();
	~CrTransform();

	SharedPtr<CrTransform> GetParent();
	FuncGetSet(Vector3f, Position);
	FuncGetSet(Vector3f, Rotation);
	FuncGetSet(Vector3f, LocalPosition);
	FuncGetSet(Vector3f, LocalRotation);
	FuncGetSet(Vector3f, LocalScale);
	EasyGetFuncOnly(Vector3f, m_v3Forword, Forword);
	EasyGetFuncOnly(Vector3f, m_v3Right, Right);
	EasyGetFuncOnly(Vector3f, m_v3Up, Up);

	EasyGetFuncOnly(Matrix4, m_m4LocalToWorld, LocalToWorldMatrix);
	EasyGetFuncOnly(Matrix4, m_m4WorldToLocal, WorldToLocalMatrix);

	EasyGetFuncOnly(Quaternion, m_qQuaternion, Quaternion);
	EasyGetFuncOnly(Quaternion, m_qLocalQuaternion, LocalQuaternion);

	void LookAt(SharedPtr<CrGameObject> gameobject);
	void LookAt(SharedPtr<CrTransform> transform);
	void LookAt(Vector3f position);

	Vector3f GetScale();
	void SetParent(SharedPtr<CrTransform> pParent);
	CEVector<SharedPtr<CrTransform>> get_children() { return m_pChildren; }
private:
	void SetRotationDirty();
	void SetPositionDirty();
	void SetScaleDirty();
	
	void _ExecuteMatrix();
	
	void RemoveChild(SharedPtr<CrTransform> pChild);
	void RemoveAllChild();
private:

	Vector3f m_v3Position;
	Vector3f m_v3Rotation;
	Vector3f m_v3Scale;

	Vector3f m_v3LocalPosition;
	Vector3f m_v3LocalRotation;
	Vector3f m_v3LocalScale;

	bool m_isPositionDirty;
	bool m_isRotationDirty;
	bool m_isScaleDirty;

	bool m_isMatrixDirty;

	Vector3f m_xAxis;
	Vector3f m_yAxis;
	Vector3f m_zAxis;

	CEVector<SharedPtr<CrTransform>> m_pChildren;
	WeakPtr<CrTransform> m_pParent;
};
#endif