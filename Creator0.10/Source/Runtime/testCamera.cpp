#include "testCamera.h"
#include <glm.hpp>

testCamera::testCamera()
	: a(0.f)
	, b(0.f)
	, bb(1.f)
{

}

testCamera::~testCamera()
{

}

void testCamera::Awake()
{
	AddEventListen(Func_Event(testCamera::EventCallback));
}

void testCamera::Destroy()
{
	RemoveEventListen(Func_Event(testCamera::EventCallback));
}

void testCamera::Update()
{

}

void testCamera::EventCallback(GLint64 msg, GLint64 wParam, GLint64 lParam)
{
	float _speed = 5.f;
	if (msg == CR_EVENT_KEY && wParam == GLFW_REPEAT)
	{
		glm::vec3 _pos;
		glm::vec3 _move;
		float _dt;

		switch (lParam)
		{
		case GLFW_KEY_W:
			_pos = GetGameObject()->GetTransform()->GetPosition();
			_move = GetGameObject()->GetTransform()->GetForword();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->GetTransform()->SetPosition(_pos - _move  * _dt * _speed);
			break;
		case GLFW_KEY_S:
			_pos = GetGameObject()->GetTransform()->GetPosition();
			_move = GetGameObject()->GetTransform()->GetForword();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->GetTransform()->SetPosition(_pos + _move  * _dt * _speed);
			break;
		case GLFW_KEY_A:
			_pos = GetGameObject()->GetTransform()->GetPosition();
			_move = GetGameObject()->GetTransform()->GetRight();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->GetTransform()->SetPosition(_pos - _move  * _dt * _speed);
			break;
		case GLFW_KEY_D:
			_pos = GetGameObject()->GetTransform()->GetPosition();
			_move = GetGameObject()->GetTransform()->GetRight();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->GetTransform()->SetPosition(_pos + _move  * _dt * _speed);
			break;
		default:
			break;
		}
	}

	if (msg == CR_EVENT_MOUSE_MOVE)
	{
		GetGameObject()->GetTransform()->SetRotation(GetGameObject()->GetTransform()->GetRotation() - Vector3(lParam, wParam, 0) * CrTime::Instance()->GetDelateTime()* _speed);
	}
}