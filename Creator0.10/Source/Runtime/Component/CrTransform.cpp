#include <CrTransform.h>
#include <CrGameObject.h>

CrTransform::CrTransform()
	:m_isDirty(true)
	, m_v3Scale(1.f, 1.f, 1.f)
{
}

CrTransform::~CrTransform()
{
}

glm::vec3 CrTransform::GetPosition()
{
	if (m_isPositionDirty)
	{
		CrTransform * parentTransform = GetGameObject() && GetGameObject()->GetParent() ? GetGameObject()->GetParent()->GetTransform() : NULL;
		if (parentTransform)
		{
			m_v3Position = glm::vec3(parentTransform->GetLocalToWorldMatrix() * glm::vec4(m_v3LocalPosition, 1.f));
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
		CrTransform * parentTransform = GetGameObject() && GetGameObject()->GetParent() ? GetGameObject()->GetParent()->GetTransform() : NULL;
		if (parentTransform)
		{
			m_v3Rotation = parentTransform->GetRotation() + m_v3LocalRotation;
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
		CrTransform * parentTransform = GetGameObject() && GetGameObject()->GetParent() ? GetGameObject()->GetParent()->GetTransform() : NULL;
		if (parentTransform)
		{
			m_v3Scale = parentTransform->GetScale() * m_v3LocalScale;
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

	CrTransform * parentTransform = GetGameObject() && GetGameObject()->GetParent() ? GetGameObject()->GetParent()->GetTransform() : NULL;
	if (parentTransform)
	{
		m_v3LocalPosition = glm::vec3(parentTransform->GetWorldToLocalMatrix() * glm::vec4(m_v3Position, 1.f));
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

	CrTransform * parentTransform = GetGameObject() && GetGameObject()->GetParent() ? GetGameObject()->GetParent()->GetTransform() : NULL;
	if (parentTransform)
	{
		m_v3LocalRotation = m_v3Rotation - parentTransform->GetRotation();
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
		m_v3Forword = glm::vec3(m_m4LocalToWorld * glm::vec4(0.f, 0.f, 1.f, 1.f));
		m_v3Up = glm::vec3(m_m4LocalToWorld * glm::vec4(0.f, 1.f, 0.f, 1.f));
		m_v3Right = glm::vec3(m_m4LocalToWorld * glm::vec4(1.f, 0.f, 0.f, 1.f));

		m_isDirty = false;
	}
}

glm::quat CrTransform::GetQuaternion()
{
	return glm::quat(GetRotation() * glm::pi<float>() / 180.f);
}

void CrTransform::LookAt(CrGameObject * gameobject)
{
	if (gameobject == NULL)
		return;

	LookAt(gameobject->GetTransform()->GetPosition());
}
void CrTransform::LookAt(CrTransform * transform)
{
	if (transform == NULL)
		return;
	LookAt(transform->GetPosition());
}
void CrTransform::LookAt(glm::vec3 position)
{
	//glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	//m_zAxis = glm::normalize(GetPosition() - position);
	//m_xAxis = glm::normalize(glm::cross(worldUp, -m_zAxis));
	//m_yAxis = glm::cross(m_zAxis, m_xAxis);

	m_m4LocalToWorld = glm::lookAt(GetPosition(), position, glm::vec3(0.f, 1.f, 0.f));
	glm::quat quat = glm::quat(m_m4LocalToWorld);
	
	glm::vec3 r = glm::eulerAngles(quat) * 360.f;

	SetRotation(r);
}

void CrTransform::SetChildrenPositionDirty()
{
	m_isPositionDirty = true;
	m_isDirty = true;

	if (GetGameObject() == NULL)
		return;

	std::vector<CrGameObject*> children = GetGameObject()->GetChildren();
	std::vector<CrGameObject*>::iterator iter = children.begin();
	std::vector<CrGameObject*>::iterator iterEnd = children.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->GetTransform()->SetChildrenPositionDirty();
	}
}

void CrTransform::SetChildrenRotationDirty()
{
	m_isPositionDirty = true;
	m_isRotationDirty = true;
	m_isDirty = true;

	if (GetGameObject() == NULL)
		return;

	std::vector<CrGameObject*> children = GetGameObject()->GetChildren();
	std::vector<CrGameObject*>::iterator iter = children.begin();
	std::vector<CrGameObject*>::iterator iterEnd = children.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->GetTransform()->SetChildrenRotationDirty();
	}
}

void CrTransform::SetChildrenScaleDirty()
{
	m_isPositionDirty = true;
	m_isScaleDirty = true;
	m_isDirty = true;

	if (GetGameObject() == NULL)
		return;

	std::vector<CrGameObject*> children = GetGameObject()->GetChildren();
	std::vector<CrGameObject*>::iterator iter = children.begin();
	std::vector<CrGameObject*>::iterator iterEnd = children.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->GetTransform()->SetChildrenScaleDirty();
	}
}
