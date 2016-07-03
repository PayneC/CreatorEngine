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
#include <CrScene.h>

class CrEngine : public CrSingleton<CrEngine>
{

public:
	int Initialization();
	int Start(CrScene * pScene);
	void Stop();

public:
	static CrMemoryPool * MemoryPool() { return m_pInstance->m_pMemoryPool; }
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
private:
	bool m_isInit;
	CrMemoryPool * m_pMemoryPool;
	double m_lfTotalDelay;

	CrScene * m_pRunScene;
	std::list<CrCamera*> m_pCameraList;
};

#endif