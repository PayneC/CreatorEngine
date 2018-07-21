#include <CrGameObject.h>
#include <CrTransform.h>

CrTransform::CrTransform()
	:m_isDirty(true)
	, m_v3Scale(1.f, 1.f, 1.f)
	, m_pParent()
{
}

CrTransform::~CrTransform()
{
}

std::shared_ptr<CrTransform> CrTransform::GetParent()
{
	return std::shared_ptr<CrTransform>(m_pParent);
}

glm::vec3 CrTransform::GetPosition()
{
	if (m_isPositionDirty)
	{
		if (!m_pParent.expired())
		{
			m_v3Position = glm::vec3(GetParent()->GetLocalToWorldMatrix() * glm::vec4(m_v3LocalPosition, 1.f));
		}
		else
		{
			m_v3Position = m_v3LocalPosition;
		}

		m_isPositionDirty = false;
	}
	return m_v3Position;
}

glm::vec3 CrTransform::GetRotation()
{
	if (m_isRotationDirty)
	{
		if (!m_pParent.expired())
		{
			m_v3Rotation = GetParent()->GetRotation() + m_v3LocalRotation;
		}
		else
		{
			m_v3Rotation = m_v3LocalRotation;
		}

		m_isRotationDirty = false;
	}

	return m_v3Rotation;
}

glm::vec3 CrTransform::GetScale()
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

glm::vec3 CrTransform::GetLocalPosition()
{
	return m_v3LocalPosition;
}

glm::vec3 CrTransform::GetLocalRotation()
{
	return m_v3LocalRotation;
}

glm::vec3 CrTransform::GetLocalScale()
{
	return m_v3LocalScale;
}
glm::vec3 CrTransform::GetForword()
{
	_ExecuteMatrix();
	return m_v3Forword;
}

glm::vec3 CrTransform::GetRight()
{
	_ExecuteMatrix();
	return m_v3Right;
}

glm::vec3 CrTransform::GetUp()
{
	_ExecuteMatrix();
	return m_v3Up;
}

glm::mat4 CrTransform::GetLocalToWorldMatrix()
{
	_ExecuteMatrix();
	return m_m4LocalToWorld;
}

glm::mat4 CrTransform::GetWorldToLocalMatrix()
{
	_ExecuteMatrix();
	return m_m4WorldToLocal;
}

void CrTransform::SetPosition(glm::vec3 var)
{
	if (m_v3Position == var)
		return;
	m_v3Position = var;

	if (!m_pParent.expired())
	{
		m_v3LocalPosition = glm::vec3(GetParent()->GetWorldToLocalMatrix() * glm::vec4(m_v3Position, 1.f));
	}
	else
	{
		m_v3LocalPosition = m_v3Position;
	}

	SetChildrenPositionDirty();
	m_isPositionDirty = false;
}

void CrTransform::SetRotation(glm::vec3 var)
{
	if (m_v3Rotation == var)
		return;

	m_v3Rotation = var;
	m_qQuaternion = glm::quat(m_v3Rotation * glm::pi<float>() / 180.f);

	m_v3Forword = glm::vec3(m_qQuaternion * glm::vec4(0.f, 0.f, 1.f, 1.f));
	m_v3Up = glm::vec3(m_qQuaternion * glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_v3Right = glm::vec3(m_qQuaternion * glm::vec4(1.f, 0.f, 0.f, 1.f));

	if (!m_pParent.expired())
	{
		glm::quat quat = GetParent()->GetQuaternion() * m_qQuaternion;
		m_v3LocalRotation = glm::eulerAngles(quat) * 360.f;
	}
	else
	{
		m_v3LocalRotation = m_v3Rotation;
	}

	SetChildrenRotationDirty();
	m_isRotationDirty = false;
}

void CrTransform::SetLocalPosition(glm::vec3 var)
{
	if (m_v3LocalPosition == var)
		return;

	m_v3LocalPosition = var;
	SetChildrenPositionDirty();
	m_isScaleDirty = false;
}

void CrTransform::SetLocalRotation(glm::vec3 var)
{
	if (m_v3LocalRotation == var)
		return;

	m_v3LocalRotation = var;

	if (!m_pParent.expired())
	{
		glm::quat _quat = glm::quat(m_v3LocalRotation * glm::pi<float>() / 180.f);
		m_qQuaternion = GetParent()->GetQuaternion() * _quat;
		m_v3Rotation = glm::eulerAngles(m_qQuaternion) * 360.f;
	}
	else
	{
		m_v3Rotation = m_v3LocalRotation;
		m_qQuaternion = glm::quat(m_v3LocalRotation * glm::pi<float>() / 180.f);
	}

	m_v3Forword = glm::vec3(m_qQuaternion * glm::vec4(0.f, 0.f, 1.f, 1.f));
	m_v3Up = glm::vec3(m_qQuaternion * glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_v3Right = glm::vec3(m_qQuaternion * glm::vec4(1.f, 0.f, 0.f, 1.f));

	SetChildrenRotationDirty();
}

void CrTransform::SetLocalScale(glm::vec3 var)
{
	if (m_v3LocalScale == var)
		return;

	m_v3LocalScale = var;
	SetChildrenScaleDirty();
}

void CrTransform::_ExecuteMatrix()
{
	if (m_isDirty)
	{
		glm::mat4 rm = glm::mat4(GetQuaternion());
		glm::mat4 sm = glm::scale(glm::mat4(1.f), GetScale());
		glm::mat4 tm = glm::translate(glm::mat4(1.f), GetPosition());

		m_m4LocalToWorld = tm * sm * rm;
		m_m4WorldToLocal = glm::inverse(m_m4LocalToWorld);

		m_isDirty = false;
	}
}

void CrTransform::SetParent(std::shared_ptr<CrTransform> pParent)
{
	std::shared_ptr<CrTransform> _parent = m_pParent.lock();
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

	m_pParent = std::weak_ptr<CrTransform>(_parent);
}

glm::quat CrTransform::GetQuaternion()
{
	return m_qQuaternion;
}

void CrTransform::LookAt(std::shared_ptr<CrGameObject> gameobject)
{
	if (gameobject == NULL)
		return;

	LookAt(gameobject->get_transform()->GetPosition());
}
void CrTransform::LookAt(std::shared_ptr<CrTransform> transform)
{
	if (transform == NULL)
		return;
	LookAt(transform->GetPosition());
}
void CrTransform::LookAt(glm::vec3 position)
{
	m_m4LocalToWorld = glm::lookAt(GetPosition(), position, glm::vec3(0.f, 1.f, 0.f));
	glm::quat quat = glm::quat(m_m4LocalToWorld);

	glm::vec3 r = glm::eulerAngles(quat) * 360.f;

	SetRotation(r);
}

void CrTransform::SetChildrenPositionDirty()
{
	m_isPositionDirty = true;
	m_isDirty = true;

	std::vector<std::shared_ptr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<std::shared_ptr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetChildrenPositionDirty();
	}
}

void CrTransform::SetChildrenRotationDirty()
{
	m_isPositionDirty = true;
	m_isRotationDirty = true;
	m_isDirty = true;

	std::vector<std::shared_ptr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<std::shared_ptr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetChildrenRotationDirty();
	}
}

void CrTransform::SetChildrenScaleDirty()
{
	m_isPositionDirty = true;
	m_isScaleDirty = true;
	m_isDirty = true;

	std::vector<std::shared_ptr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<std::shared_ptr<CrTransform>>::iterator iterEnd = m_pChildren.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetChildrenScaleDirty();
	}
}

void CrTransform::RemoveChild(std::shared_ptr<CrTransform> pChild)
{
	if (!pChild)
		return;

	std::vector<std::shared_ptr<CrTransform>>::iterator iter = m_pChildren.begin();
	std::vector<std::shared_ptr<CrTransform>>::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == pChild)
			break;
	}
	if (iter != iterEnd)
	{
		m_pChildren.erase(iter);
	}
}

void CrTransform::RemoveAllChild()
{
	m_pChildren.clear();
}
