/*
CreatorEngine
Class CrWindow
Payne
*/

#ifndef _CREATOR_WINDOW_H
#define _CREATOR_WINDOW_H

#include <CrDefine.h>

// GLFW
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif

#include <glfw3native.h>

static class DLL_ClASS CrWindow
{
public:
	static bool Create();
	static void Update();
#ifdef _WIN32
	static HWND GetWin32WindowHWND();
#endif
	static glm::uvec2 GetWindowSize();
	static void SetWindowSize(glm::uvec2);
	static GLFWwindow* GetEngineWindow();
	static glm::uvec2 GetCenter();

	static glm::dvec2 m_v2Mouse;
private:
	static glm::dvec2 m_v2Center;
	static glm::uvec2 m_v2WindowSize;
	static std::string m_strWindowName;
	static GLFWwindow* m_pEngineWindow;
};

#endif