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

		switch (lParam)
		{
		case GLFW_KEY_W:
			GetGameObject()->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition() - GetGameObject()->GetTransform()->GetForword() * CrTime::Instance()->GetDelateTime() * _speed);
			break;
		case GLFW_KEY_S:
			GetGameObject()->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition() + GetGameObject()->GetTransform()->GetForword() * CrTime::Instance()->GetDelateTime()* _speed);
			break;
		case GLFW_KEY_A:
			GetGameObject()->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition() - GetGameObject()->GetTransform()->GetRight() * CrTime::Instance()->GetDelateTime()* _speed);
			break;
		case GLFW_KEY_D:
			GetGameObject()->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition() + GetGameObject()->GetTransform()->GetRight() * CrTime::Instance()->GetDelateTime()* _speed);
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