#include <CrWindow.h>
#include <Event.h>

void KeyCallBack(GLFWwindow* pWindow, int keyCode, int scanCode, int action, int Crds)
{
	printf("%d-%d-%d-%d \n", keyCode, scanCode, action, Crds);
	Event::ProMessage(CR_EVENT_KEY, action, keyCode);

}
void CursorPosCallback(GLFWwindow* pWindow, double xPos, double yPos)
{
	//printf("%lf-%lf \n", xPos, yPos);
	GLdouble a, b;
	a = xPos - CrWindow::m_v2Mouse.x;
	b = yPos - CrWindow::m_v2Mouse.y;

	CrWindow::m_v2Mouse.x = xPos;
	CrWindow::m_v2Mouse.y = yPos;

	//glfwSetCursorPos(pWindow, CrWindow::GetCenter().x, CrWindow::GetCenter().y);

	Event::ProMessage(CR_EVENT_MOUSE_MOVE, a, b);// CrWindow::m_v2Mouse.x, CrWindow::m_v2Mouse.y);
}

void MouseButtonCallback(GLFWwindow* pWindow, int keyCode, int action, int Crds)
{
	printf("%d-%d-%d \n", keyCode, action, Crds);
	Event::ProMessage(CR_EVENT_MOUSE_BUTTON, action, keyCode);
}

void ScrollCallback(GLFWwindow* pWindow, double xOffest, double yOffest)
{	
	Event::ProMessage(CR_EVENT_MOUSE_WHEEL, xOffest, yOffest);
}

glm::dvec2 CrWindow::m_v2Mouse(0, 0);
glm::dvec2 CrWindow::m_v2Center(683, 384);
glm::uvec2 CrWindow::m_v2WindowSize(1366, 768);
std::string CrWindow::m_strWindowName("CreatorEngine");
GLFWwindow* CrWindow::m_pEngineWindow(NULL);

bool CrWindow::Create()
{
	m_pEngineWindow = glfwCreateWindow(m_v2WindowSize.x, m_v2WindowSize.y, m_strWindowName.c_str(), nullptr, nullptr);
	if (m_pEngineWindow)
	{
		glfwMakeContextCurrent(m_pEngineWindow);

		glfwSetInputMode(m_pEngineWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetKeyCallback(m_pEngineWindow, KeyCallBack);
		glfwSetCursorPosCallback(m_pEngineWindow, CursorPosCallback);
		glfwSetMouseButtonCallback(m_pEngineWindow, MouseButtonCallback);
		glfwSetScrollCallback(m_pEngineWindow, ScrollCallback);

		glm::uvec2 _pos = GetWindowSize();
		m_v2Center.x = _pos.x * 0.5;
		m_v2Center.y = _pos.y * 0.5;

		glfwGetCursorPos(m_pEngineWindow, &(m_v2Center.x), &(m_v2Center.y));

		return true;
	}
	glfwTerminate();

	return false;
}

glm::uvec2 CrWindow::GetWindowSize()
{
	return m_v2WindowSize;
}

void CrWindow::SetWindowSize(glm::uvec2 size)
{
	m_v2WindowSize = size;
	glfwSetWindowSize(m_pEngineWindow, size.x, size.y);

	m_v2Center.x = m_v2WindowSize.x * 0.5;
	m_v2Center.y = m_v2WindowSize.y * 0.5;
}

glm::uvec2 CrWindow::GetCenter()
{
	return m_v2Center;
}

GLFWwindow* CrWindow::GetEngineWindow()
{
	return m_pEngineWindow;
}

void CrWindow::Update()
{
	glfwSwapBuffers(m_pEngineWindow);	
}

#ifdef _WIN32
HWND CrWindow::GetWin32WindowHWND()
{
	return glfwGetWin32Window(m_pEngineWindow);
}
#endif