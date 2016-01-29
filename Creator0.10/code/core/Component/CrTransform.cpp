#include <CrTransform.h>
#include <CrGameObject.h>

CrTransform::CrTransform()
{
}

CrTransform::~CrTransform()
{
}

glm::vec3 CrTransform::GetPostion()
{
	_ExecutePostion();
	return m_v3Postion;
}

glm::vec3 CrTransform::GetRotation()
{
	_ExecutePostion();
	return m_v3Rotation;
}

glm::vec3 CrTransform::GetScale()
{
	_ExecutePostion();
	return m_v3Scale;
}

glm::vec3 CrTransform::GetLocalPostion()
{
	_ExecutePostion();
	return m_v3LocalPostion;
}

glm::vec3 CrTransform::GetLocalRotation()
{
	_ExecutePostion();
	return m_v3LocalRotation;
}

glm::vec3 CrTransform::GetLocalScale()
{
	_ExecutePostion();
	return m_v3LocalScale;
}
glm::vec3 CrTransform::GetForword()
{
	_ExecutePostion();
	return m_v3Forword;
}

glm::vec3 CrTransform::GetLeft()
{
	_ExecutePostion();
	return m_v3Left;
}

glm::vec3 CrTransform::GetUp()
{
	_ExecutePostion();
	return m_v3Up;
}

glm::mat4 CrTransform::GetLocalToWorldMatrix()
{
	_ExecutePostion();
	return m_m4LocalToWorld;
}

glm::mat4 CrTransform::GetWorldToLocalMatrix()
{
	_ExecutePostion();
	return m_m4WorldToLocal;
}

void CrTransform::SetPostion(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_LP) || m_v3Postion != var)
	{
		_RemoveDirtyFlag(TDF_LP);

		m_v3Postion = var;
		_AddDirtyFlag(TDF_GP);		
	}
}

void CrTransform::SetRotation(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_LR) || m_v3Rotation != var)
	{
		_RemoveDirtyFlag(TDF_LR);

		m_v3Rotation = var;
		_AddDirtyFlag(TDF_GR);		
	}
}

void CrTransform::SetScale(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_LS) || m_v3Scale != var)
	{
		_RemoveDirtyFlag(TDF_LS);
		
		m_v3Scale = var;
		_AddDirtyFlag(TDF_GS);
	}	
}

void CrTransform::SetLocalPostion(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_GP) || m_v3LocalPostion != var)
	{
		_RemoveDirtyFlag(TDF_GP);

		m_v3LocalPostion = var;
		_AddDirtyFlag(TDF_LP);
	}
}

void CrTransform::SetLocalRotation(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_GR) || m_v3LocalRotation != var)
	{
		_RemoveDirtyFlag(TDF_GR);

		m_v3LocalRotation = var;
		_AddDirtyFlag(TDF_LR);	
	}
}

void CrTransform::SetLocalScale(glm::vec3 var)
{
	if (_CheckDirtyFlag(TDF_GS) || m_v3LocalScale != var)
	{
		_RemoveDirtyFlag(TDF_GS);

		m_v3LocalScale = var;
		_AddDirtyFlag(TDF_LS);		
	}
}

void CrTransform::_AddDirtyFlag(uint64_t flag)
{
	m_uDirtyFlags |= flag;
}

void CrTransform::_RemoveDirtyFlag(uint64_t flag)
{
	m_uDirtyFlags &= (~flag);
}

bool CrTransform::_CheckDirtyFlag(uint64_t flag)
{
	return m_uDirtyFlags & flag;
}

void CrTransform::_ExecuteTranslate()
{
	if (m_uDirtyFlags != 0)
	{		
		_ExecuteRotation();
		_ExecuteScale();
		_ExecutePostion();
	}
}

void CrTransform::_ExecutePostion()
{
	if (_CheckDirtyFlag(TDF_LP) || _CheckDirtyFlag(TDF_GP))
	{
		if (_CheckDirtyFlag(TDF_LP))
		{
			if (GetGameObject() && GetGameObject()->GetParent() && GetGameObject()->GetParent()->GetTransform())
			{
				m_v3Postion = glm::vec3(GetGameObject()->GetTransform()->GetWorldToLocalMatrix() * glm::vec4(m_v3LocalPostion, 1.0f));
			}
			else
			{
				m_v3Postion = m_v3LocalPostion;
			}
			_RemoveDirtyFlag(TDF_LP);
		}
		else
		{
			if (GetGameObject() && GetGameObject()->GetParent() && GetGameObject()->GetParent()->GetTransform())
			{
				m_v3LocalPostion = glm::vec3(GetGameObject()->GetTransform()->GetWorldToLocalMatrix() * glm::vec4(m_v3Postion, 1.0f));
			}
			else
			{
				m_v3LocalPostion = m_v3Postion;
			}
			_RemoveDirtyFlag(TDF_GP);
		}
	}
}

void CrTransform::_ExecuteRotation()
{
	if (_CheckDirtyFlag(TDF_LR) || _CheckDirtyFlag(TDF_GR))
	{
		if (_CheckDirtyFlag(TDF_LR))
		{
			if (GetGameObject() && GetGameObject()->GetParent() && GetGameObject()->GetParent()->GetTransform())
			{
				m_v3Rotation = glm::vec3(GetGameObject()->GetTransform()->GetQuaternion() * glm::vec4(m_v3LocalRotation, 1.0f));
			}
			else
			{
				m_v3Rotation = m_v3LocalRotation;
			}
			_RemoveDirtyFlag(TDF_LR);
		}
		else
		{
			if (GetGameObject() && GetGameObject()->GetParent() && GetGameObject()->GetParent()->GetTransform())
			{
				//m_v3LocalRotation = glm::vec3(GetGameObject()->GetTransform()->GetQuaternion() * glm::vec4(m_v3Rotation, 1.0f));
			}
			else
			{
				m_v3LocalRotation = m_v3Rotation;
			}
			_RemoveDirtyFlag(TDF_GR);
		}
	}
}

void CrTransform::_ExecuteScale()
{
	
}

void CrTransform::_ExecuteMatrix()
{
	m_m4LocalToWorld = glm::mat4(GetQuaternion());
	m_m4LocalToWorld = glm::scale(m_m4LocalToWorld, m_v3Scale);
	m_m4LocalToWorld = glm::translate(m_m4LocalToWorld, m_v3Postion);
}

glm::quat CrTransform::GetQuaternion()
{
	return glm::quat(m_v3Rotation);
}