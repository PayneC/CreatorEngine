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
#include "CrDirector.h"
#include "CrMemoryPool.h"
#include "CrWindow.h"

class CrEngine : public CrSingleton<CrEngine>
{
	friend void KeyCallBack(GLFWwindow* window, int keyCode, int scanCode, int action, int Crds);
	friend void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	friend void CruseButtonCallback(GLFWwindow* window, int keyCode, int action, int Crds);

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
	void ProMessage(GLFWwindow* window, GLuint64 msg, unsigned __int64 wParam, unsigned __int64 lParam);

private:
	bool m_isInit;

	CrMemoryPool * m_pMemoryPool;

	double m_lfTotalDelay;

	CrModel * m_pModel;
	glm::mat4 m_mat4;
	glm::vec3 m_vec3;
	float r;
	glm::vec3 m_r;
};

#endif