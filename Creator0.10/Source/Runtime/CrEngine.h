/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINE_H
#define _CREATOR_ENGINE_H

#include <cstdio>
#include <stdlib.h>

#include "CrSingleton.h"

#include "CrConfig.h"
#include "CrTime.h"
#include "CrShaderUtility.h"
#include "CrEvent.h"
#include "CrMemoryPool.h"
#include "CrWindow.h"

#include <CrCamera.h>
#include <UICanvas.h>
#include <Core/CrScene.h>

class DLL_ClASS CrEngine : public CrSingleton<CrEngine>
{

public:
	int Initialization();
	int Start(CrScene * pScene);
	void Stop();

private:
	bool m_isRun;

public:
	CrEngine();
	~CrEngine();

private:

	bool Init();
	void Destory();
	void OnEnter();
	int MainLoop();
	void OnExit();

public:
	void ProMessage(GLFWwindow* window, GLuint64 msg, unsigned __int64 wParam, unsigned __int64 lParam);

	void AddCamera(CrCamera * pCamera);
	void RemoveCamera(CrCamera * pCamera);

	void AddCanvas(UICanvas * pCanvas);
	void RemoveCanvas(UICanvas * pCanvas);
private:
	bool m_isInit;
	double m_lfTotalDelay;

	CrScene * m_pRunScene;
	std::list<CrCamera*> m_pCameraList;
	std::list<UICanvas*> m_pCanvasList;
};

#endif