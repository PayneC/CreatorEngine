#include "CrEvent.h"
#include "CrEngine.h"
#include <glfw3.h>
#include <glm.hpp>

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
	:m_isInit(false)
{

}

CrEvent::~CrEvent()
{
	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (; iter != iterEnd; ++iter)
	{
		entry = (*iter);		
		delete(entry);
	}
	m_eventListenEntrys.clear();
}

bool CrEvent::Init()
{
	GLFWwindow * pWindow = CrWindow::Instance()->GetEngineWindow();
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(pWindow, KeyCallBack);
	glfwSetCursorPosCallback(pWindow, CursorPosCallback);
	glfwSetMouseButtonCallback(pWindow, CruseButtonCallback);

	//glfwGetCursorPos(pWindow, &m_mousePosX, &m_mousePosY);	
	glm::uvec2 _pos = CrWindow::Instance()->GetWindowSize();
	m_mousePosX = _pos.x * 0.5;
	m_mousePosY = _pos.y * 0.5;
	return true;
}

void CrEvent::ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam)
{
	GLint64 a, b;

	if (msg == CR_EVENT_MOUSE_MOVE)
	{
		if (!m_isInit)
		{
			m_isInit = true;
			a = 0;
			b = 0;
		}
		else
		{
			a = wParam - m_mousePosX;
			b = lParam - m_mousePosY;
		}

		m_mousePosX = wParam;
		m_mousePosY = lParam;
		GLFWwindow * pWindow = CrWindow::Instance()->GetEngineWindow();
		glfwSetCursorPos(pWindow, m_mousePosX, m_mousePosY);
	}
	else
	{
		a = wParam;
		b = lParam;
	}

	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (;iter != iterEnd; ++iter)
	{
		entry = (*iter);
		((entry->object)->*(entry->func))(msg, a, b);
	}
}

void CrEvent::Update()
{
	glfwPollEvents();
}

void CrEvent::_AddListen(EventListenEntry * entry)
{
	if (entry)
		m_eventListenEntrys.push_back(entry);
}

void CrEvent::AddListen(CrObject * object, EventFunc func)
{
	EventListenEntry * entry = new EventListenEntry();
	entry->object = object;
	entry->func = func;
	_AddListen(entry);
}

void CrEvent::RemoveListen(CrObject * object, EventFunc func)
{
	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (; iter != iterEnd; ++iter)
	{
		entry = (*iter);
		if (entry->object == object && entry->func == func)
		{
			m_eventListenEntrys.erase(iter);
			delete(entry);
			break;
		}
	}
}