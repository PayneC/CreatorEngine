/*
CreatorEngine
Class CrWindow
Payne
*/

#ifndef _CREATOR_WINDOW_H
#define _CREATOR_WINDOW_H

#include <string>
#include "CrDefine.h"
#include <CrSingleton.h>

// GLFW
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif
#include <glfw3native.h>

class DLL_ClASS CrWindow : public CrSingleton<CrWindow>
{
public:
	CrWindow();
	~CrWindow();

public:
	bool Init();
	void Update();
#ifdef _WIN32
	HWND GetWin32WindowHWND();
#endif

	EasyGetSetFuncOnly(glm::uvec2, m_v2WindowSize, WindowSize);
	EasyGetSetFuncOnly(std::string, m_strWindowName, WindowName);
	EasyGet(GLFWwindow*, m_pEngineWindow, EngineWindow);

private:
	

};

#endif