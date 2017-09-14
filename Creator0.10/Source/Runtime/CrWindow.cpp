#include "CrWindow.h"

CrWindow::CrWindow()
: m_pEngineWindow(NULL)
, m_v2WindowSize(1366,768)
, m_strWindowName("CreatorEngine")
{
}

CrWindow::~CrWindow()
{
}

bool CrWindow::Init()
{
	m_pEngineWindow = glfwCreateWindow(m_v2WindowSize.x, m_v2WindowSize.y, m_strWindowName.c_str(), nullptr, nullptr);
	if (m_pEngineWindow)
	{
		glfwMakeContextCurrent(m_pEngineWindow);
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
	glfwSetWindowSize(m_pEngineWindow, size.x, size.y);
}

std::string CrWindow::GetWindowName()
{
	return m_strWindowName;
}

void CrWindow::SetWindowName(std::string name)
{
	glfwSetWindowTitle(m_pEngineWindow, name.c_str());
}

void CrWindow::Update()
{
	glfwSwapBuffers(m_pEngineWindow);
}