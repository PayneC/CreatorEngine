#include "CrEvent.h"
#include "CrEngine.h"
#include <glfw\glfw3.h>

void KeyCallBack(GLFWwindow* pWindow, int keyCode, int scanCode, int action, int Crds)
{
	printf("%d-%d-%d-%d \n", keyCode, scanCode, action, Crds);
	CrEngine::Instance()->ProMessage(pWindow, CR_EVENT_KEY, action, keyCode);
}
void CursorPosCallback(GLFWwindow* pWindow, double xPos, double yPos)
{
	//printf("%lf-%lf \n", xPos, yPos);
	CrEngine::Instance()->ProMessage(pWindow, CR_EVENT_MOUSE_MOVE, xPos, yPos);
}

void CruseButtonCallback(GLFWwindow* pWindow, int keyCode, int action, int Crds)
{
	printf("%d-%d-%d \n", keyCode, action, Crds);
	CrEngine::Instance()->ProMessage(pWindow, CR_EVENT_MOUSE_BUTTON, action, keyCode);
}

CrEvent::CrEvent()
{

}

CrEvent::~CrEvent()
{

}

bool CrEvent::Init()
{
	GLFWwindow * pWindow = CrWindow::Instance()->GetEngineWindow();
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetKeyCallback(pWindow, KeyCallBack);
	glfwSetCursorPosCallback(pWindow, CursorPosCallback);
	glfwSetMouseButtonCallback(pWindow, CruseButtonCallback);
	return true;
}

void CrEvent::ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam)
{
	if (msg == CR_EVENT_KEY && wParam == GLFW_RELEASE, lParam == GLFW_KEY_ESCAPE)
	{
		
	}
}

void CrEvent::Update()
{
	glfwPollEvents();
}
