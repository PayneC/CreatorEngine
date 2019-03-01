#include <CrGameObject.h>
#include <CrTransform.h>

#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/euler_angles.hpp>

Float _angle_limit(Float a)
{
	if (a > 180)
	{
		a = a - 360 * (int)(a / 360);
	}
	else if (a < -180)
	{
		a = a - 360 * (int)(a / 360);
	}

	if (a > 180)
	{
		return a - 360;
	}
	else if (a < -180)
	{
		return a + 360;
	}

	return a;
}

Vector3f angle_limit(Vector3f a)
{
	return Vector3f(_angle_limit(a.x), _angle_limit(a.y), _angle_limit(a.z));
}

CrTransform::CrTransform()
	: m_isMatrixDirty(false)
	, m_isPositionDirty(true)
	, m_isRotationDirty(true)
	, m_isScaleDirty(true)
	, m_v3Scale(1.f, 1.f, 1.f)
	, m_v3LocalScale(1.f, 1.f, 1.f)
	, m_pParent()
	, m_qLocalQuaternion(1, 0, 0 ,0)
	, m_qQuaternion(1, 0, 0, 0)
{
}

CrTransform::~CrTransform()
{
}

SharedPtr<CrTransform> CrTransform::GetParent()
{
	return m_pParent.lock();
}

Vector3f CrTransform::GetPosition()
{
	if (m_isPositionDirty)
	{
		if (!m_pParent.expired())
		{
			m_v3Position = Vector3f(GetParent()->GetLocalToWorldMatrix() * Vector4f(m_v3LocalPosition, 1.f));
		}
		else
		{
			m_v3Position = m_v3LocalPosition;
		}

		m_isPositionDirty = false;
	}
	return m_v3Position;
}

Vector3f CrTransform::GetRotation()
{
	GetQuaternion();
	return m_v3Rotation;
}

Vector3f CrTransform::GetScale()
{
	if (m_isScaleDirty)
	{
		if (!m_pParent.expired())
		{
			m_v3Scale = GetParent()->GetScale() * m_v3LocalScale;
		}
		else
		{
			m_v3Scale = m_v3LocalScale;
		}
		m_isScaleDirty = false;
	}
	return m_v3Scale;
}

Vector3f CrTransform::GetLocalPosition()
{
	return m_v3LocalPosition;
}

Quaternion CrTransform::GetLocalQuaternion()
{
	return m_qLocalQuaternion;
}

Vector3f CrTransform::GetLocalRotation()
{
	return m_v3LocalRotation;
}

Vector3f CrTransform::GetLocalScale()
{
	return m_v3LocalScale;
}

Vector3f CrTransform::GetForword()
{
	GetQuaternion();
	return m_v3Forword;
}

Vector3f CrTransform::GetRight()
{
	GetQuaternion();
	return m_v3Right;
}

Vector3f CrTransform::GetUp()
{
	GetQuaternion();
	return m_v3Up;
}

Matrix4 CrTransform::GetLocalToWorldMatrix()
{
	_ExecuteMatrix();
	return m_m4LocalToWorld;
}

Matrix4 CrTransform::GetWorldToLocalMatrix()
{
	_ExecuteMatrix();
	return m_m4WorldToLocal;
}

void CrTransform::SetPosition(Vector3f var)
{	
	if (m_v3Position == var)
		return;

	m_v3Position = var;
	if (!m_pParent.expired())
	{
		m_v3LocalPosition = Vector3f(GetParent()->GetWorldToLocalMatrix() * Vector4f(m_v3Position, 1.f));
	}
	else
	{
		m_v3LocalPosition = m_v3Position;
	}
	
	SetPositionDirty();
	m_isPositionDirty = false;
}

void CrTransform::SetRotation(Vector3f var)
{
	if (m_v3Rotation == var)
		return;	

	m_v3Rotation = var;
	m_qQuaternion = Quaternion(m_v3Rotation * glm::pi<float>() / 180.f);	

	if (!m_pParent.expired())
	{				
		m_qLocalQuaternion = glm::inverse(GetParent()->GetQuaternion()) * m_qQuaternion;
		m_v3LocalRotation = glm::eulerAngles(m_qLocalQuaternion) / glm::pi<float>() * 180.f;
	}
	else
	{
		m_v3LocalRotation = m_v3Rotation;
		m_qLocalQuaternion = m_qQuaternion;
	}

	m_v3Forword = Vector3f(m_qQuaternion * Vector4f(0.f, 0.f, 1.f, 1.f));
	m_v3Up = Vector3f(m_qQuaternion * Vector4f(0.f, 1.f, 0.f, 1.f));
	m_v3Right = Vector3f(m_qQuaternion * Vector4f(1.f, 0.f, 0.f, 1.f));
	
	SetRotationDirty();
	m_isRotationDirty = false;
}

void CrTransform::SetLocalPosition(Vector3f var)
{
	if (m_v3LocalPosition == var)
		return;

	m_v3LocalPosition = var;
	
	SetPositionDirty();
}

void CrTransform::SetLocalRotation(Vector3f var)
{	
	var = angle_limit(var);

	if (m_v3LocalRotation == var)
		return;	

	m_v3LocalRotation = var;
	m_qLocalQuaternion = Quaternion(m_v3LocalRotation / 180.f * glm::pi<float>());

	SetRotationDirty();
}

void CrTransform::SetLocalScale(Vector3f var)
{
	if (m_v3LocalScale == var)
		return;

	m_v3LocalScale = var;
	m_isScaleDirty = true;
	
	SetScaleDirty();
}

void CrTransform::_ExecuteMatrix()
{
	if (m_isMatrixDirty)
	{
		Matrix4 rm = Matrix4(GetQuaternion());	
		Matrix4 sm = glm::scale(Matrix4(1.f), GetScale());
		Matrix4 tm = glm::translate(Matrix4(1.f), GetPosition());		

		m_m4LocalToWorld = tm * sm * rm;
		m_m4WorldToLocal = glm::inverse(m_m4LocalToWorld);

		m_isMatrixDirty = false;
	}
}

void CrTransform::SetParent(SharedPtr<CrTransform> pParent)
{	
	SharedPtr<CrTransform> _parent = m_pParent.lock();
	if (_parent == pParent)
	{
		return;
	}

	if (_parent != nullptr)
	{
		_parent->RemoveChild(shared_from_this());
	}

	_parent = pParent;

	if (_parent != nullptr)
	{
		_parent->m_pChildren.push_back(shared_from_this());
	}

	m_pParent = _parent->weak_from_this();

	SetPositionDirty();
	SetRotationDirty();
	SetScaleDirty();
}

Quaternion CrTransform::GetQuaternion()
{
	if (m_isRotationDirty)
	{
		m_isRotationDirty = false;

		if (!m_pParent.expired())
		{
			m_qQuaternion = GetParent()->GetQuaternion() * m_qLocalQuaternion;
			m_v3Rotation = glm::eulerAngles(m_qQuaternion) / glm::pi<float>() * 180.f;
		}
		else
		{
			m_v3Rotation = m_v3LocalRotation;
			m_qQuaternion = m_qLocalQuaternion;
		}

		m_v3Forword = Vector3f(m_qQuaternion * Vector4f(0.f, 0.f, 1.f, 1.f));
		m_v3Up = Vector3f(m_qQuaternion * Vector4f(0.f, 1.f, 0.f, 1.f));
		m_v3Right = Vector3f(m_qQuaternion * Vector4f(1.f, 0.f, 0.f, 1.f));
	}

	return m_qQuaternion;
}

void CrTransform::LookAt(SharedPtr<CrGameObject> gameobject)
{
	if (gameobject == NULL)
		return;

	LookAt(gameobject->get_transform()->GetPosition());
}
void CrTransform::LookAt(SharedPtr<CrTransform> transform)
{
	if (transform == NULL)
		return;
	LookAt(transform->GetPosition());
}
void CrTransform::LookAt(Vector3f position)
{
	m_m4LocalToWorld = glm::lookAt(GetPosition(), position, Vector3f(0.f, 1.f, 0.f));
	Quaternion quat = Quaternion(m_m4LocalToWorld);	

	Vector3f r = glm::eulerAngles(quat) / glm::pi<float>() * 180.f;

	SetRotation(r);
}

void CrTransform::SetPositionDirty()
{
	m_isPositionDirty = true;
	m_isMatrixDirty = true;

	std::vector<SharedPtr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetPositionDirty();
	}
}

void CrTransform::SetRotationDirty()
{
	m_isRotationDirty = true;	
	m_isMatrixDirty = true;

	std::vector<SharedPtr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetRotationDirty();
		(*iter)->SetPositionDirty();
	}
}

void CrTransform::SetScaleDirty()
{
	m_isScaleDirty = true;
	m_isMatrixDirty = true;

	std::vector<SharedPtr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetScaleDirty();
		(*iter)->SetPositionDirty();
	}
}

void CrTransform::RemoveChild(SharedPtr<CrTransform> pChild)
{
	if (!pChild)
		return;

	std::vector<SharedPtr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == pChild)
			break;
	}
	if (iter != iterEnd)
	{
		m_pChildren.erase(iter);
	}

	pChild->m_pParent.expired();
	pChild->SetPositionDirty();
	pChild->SetRotationDirty();
	pChild->SetScaleDirty();
}

void CrTransform::RemoveAllChild()
{
	std::vector<SharedPtr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		SharedPtr<CrTransform> child = (*iter);
		child->m_pParent.expired();
		child->SetPositionDirty();
		child->SetRotationDirty();
		child->SetScaleDirty();
	}

	m_pChildren.clear();
}
