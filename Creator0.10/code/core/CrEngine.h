/*
CreatorEngine
Class CrEngine : CrSingleton
Payne
*/

#ifndef _CREATOR_ENGINELOGIC_H
#define _CREATOR_ENGINELOGIC_H

#include <cstdio>
#include <stdlib.h>

#include "CrSingleton.h"

#include "CrConfig.h"
#include "CrTime.h"
#include "CrShaderUtility.h"
#include "CrEvent.h"
#include "CrRender.h"
#include "CrDirector.h"
#include "CrMemoryPool.h"
#include "CrMeshPool.h"
#include "CrWindow.h"

class CrEngine : public CrSingleton<CrEngine>
{
	friend void KeyCallBack(GLFWwindow* window, int keyCode, int scanCode, int action, int Crds);
	friend void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	friend void CruseButtonCallback(GLFWwindow* window, int keyCode, int action, int Crds);
public:
	//static CrEngine * Create();
	//static void Destory(CrEngine * & pEngine);
	static bool CreatorAwake();
	static int Launch();
	static void Stop();

	static CrConfig * Config(){ return m_pInstance->m_pConfig; }
	static CrTime * Time(){ return m_pInstance->m_pTime; }
	static CrShaderUtility * ShaderFactory() { return m_pInstance->m_pShaderFactory; }
	static CrEvent * Event() { return m_pInstance->m_pEvent; }
	static CrMemoryPool * MemoryPool() { return m_pInstance->m_pMemoryPool; }
	static CrDirector * Director() { return m_pInstance->m_pDirector; }
	static CrMeshPool * MeshPool() { return m_pInstance->m_pMeshPool; }
	static CrRender * Render() { return m_pInstance->m_pRender; }
	static CrWindow * Window() { return m_pInstance->m_pWindow; }
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

	CrConfig * m_pConfig;
	CrTime * m_pTime;
	CrShaderUtility * m_pShaderFactory;
	CrEvent * m_pEvent;
	CrMemoryPool * m_pMemoryPool;
	CrDirector * m_pDirector;
	CrMeshPool * m_pMeshPool;
	CrRender * m_pRender;
	CrWindow * m_pWindow;

	double m_lfTotalDelay;

	CrModel * m_pModel;
	glm::mat4 m_mat4;
	glm::vec3 m_vec3;
	float r;
	glm::vec3 m_r;

public:
	void TestInit();
	void TestUpdate();
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint shaderId;
};

#endif