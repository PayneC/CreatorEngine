/*
CreatorEngine
Class CrWindow
Payne
*/

#ifndef _CREATOR_WINDOW_H
#define _CREATOR_WINDOW_H

#include <string>
#include "CrDefine.h"

class CrWindow
{
	friend class CrEngine;

public:
	CrWindow();
	~CrWindow();

public:
	bool Init();

	EasyGet(GLFWwindow*, m_pEngineWindow, EngineWindow);
	EasyGetSetFuncOnly(glm::uvec2, m_v2WindowSize, WindowSize);
	EasyGetSetFuncOnly(std::string, m_strWindowName, WindowName);

private:
	void Update();

};

#endif