#include "testCamera.h"

testCamera::testCamera()
	: a(0.f)
	, b(0.f)
	, bb(1.f)
	, mouseButton3Press(false)
	, mouseButton2Press(false)
{
	Event::AddListen(this, Func_Event(testCamera::EventCallback));
}

testCamera::~testCamera()
{
	
}

void testCamera::OnDestroy()
{
	Event::RemoveListen(this, Func_Event(testCamera::EventCallback));
}

void testCamera::Update(double dt)
{

}

void testCamera::EventCallback(GLint64 msg, GLint64 wParam, GLint64 lParam)
{
	float _speed = 20.f;
	if (msg == CR_EVENT_MOUSE_BUTTON && wParam == GLFW_RELEASE)
	{
		switch (lParam)
		{
		case GLFW_MOUSE_BUTTON_3:
			mouseButton3Press = false;
			break;
		case GLFW_MOUSE_BUTTON_2:
			mouseButton2Press = false;
			break;
		default:
			break;
		}

	}

	if ((msg == CR_EVENT_KEY || msg == CR_EVENT_MOUSE_BUTTON) && (wParam == GLFW_REPEAT || wParam == GLFW_PRESS))
	{
		glm::vec3 _pos;
		glm::vec3 _move;
		float _dt;

		Vector3f rot;

		switch (lParam)
		{
		case GLFW_MOUSE_BUTTON_3:
			mouseButton3Press = true;
			break;
		case GLFW_MOUSE_BUTTON_2:
			mouseButton2Press = true;
			break;
		case GLFW_KEY_W:
			_pos = GetGameObject()->get_transform()->GetPosition();
			_move = GetGameObject()->get_transform()->GetForword();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->get_transform()->SetPosition(_pos - _move  * _dt * _speed);
			break;
		case GLFW_KEY_S:
			_pos = GetGameObject()->get_transform()->GetPosition();
			_move = GetGameObject()->get_transform()->GetForword();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->get_transform()->SetPosition(_pos + _move  * _dt * _speed);
			break;
		case GLFW_KEY_A:
			_pos = GetGameObject()->get_transform()->GetPosition();
			_move = GetGameObject()->get_transform()->GetRight();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->get_transform()->SetPosition(_pos - _move  * _dt * _speed);
			break;
		case GLFW_KEY_D:
			_pos = GetGameObject()->get_transform()->GetPosition();
			_move = GetGameObject()->get_transform()->GetRight();
			_dt = CrTime::Instance()->GetDelateTime();
			GetGameObject()->get_transform()->SetPosition(_pos + _move  * _dt * _speed);
			break;

		case GLFW_KEY_UP:			
			rot = GetGameObject()->get_transform()->GetLocalRotation();			
			rot = rot + Vector3f(1, 0, 0);
			GetGameObject()->get_transform()->SetLocalRotation(rot);
			break;

		case GLFW_KEY_DOWN:
			rot = GetGameObject()->get_transform()->GetLocalRotation();
			rot = rot - Vector3f(1, 0, 0);
			GetGameObject()->get_transform()->SetLocalRotation(rot);
			break;

		case GLFW_KEY_LEFT:
			rot = GetGameObject()->get_transform()->GetLocalRotation();
			rot = rot - Vector3f(0, 1, 0);
			GetGameObject()->get_transform()->SetLocalRotation(rot);
			break;

		case GLFW_KEY_RIGHT:
			rot = GetGameObject()->get_transform()->GetLocalRotation();
			rot = rot + Vector3f(0, 1, 0);
			GetGameObject()->get_transform()->SetLocalRotation(rot);
			break;

		case GLFW_KEY_ESCAPE:
			CrEngine::Stop();
			break;
		default:
			break;
		}
	}

	if (msg == CR_EVENT_MOUSE_MOVE && mouseButton2Press)
	{
		Vector3f rotg = GetGameObject()->get_transform()->GetRotation();
		Vector3f rot = GetGameObject()->get_transform()->GetLocalRotation();
		Vector3f dt = Vector3f(lParam, wParam, 0) * CrTime::Instance()->GetDelateTime()* _speed;
		rot = rot - dt;
		GetGameObject()->get_transform()->SetLocalRotation(rot);
	}

	if (msg == CR_EVENT_MOUSE_MOVE && mouseButton3Press)
	{
		Vector3f r = -(Float)wParam * GetGameObject()->get_transform()->GetRight() * 0.2f;
		Vector3f u = (Float)lParam * GetGameObject()->get_transform()->GetUp() * 0.2f;

		Vector3f p = GetGameObject()->get_transform()->GetPosition();
		GetGameObject()->get_transform()->SetPosition(p + r + u);
	}

	if (msg == CR_EVENT_MOUSE_WHEEL)
	{
		Vector3f f = -(Float)lParam * GetGameObject()->get_transform()->GetForword() * 0.5f;

		Vector3f p = GetGameObject()->get_transform()->GetPosition();
		GetGameObject()->get_transform()->SetPosition(p + f);
	}
}