#include "CrEngine.h"
#include <common/CrFontLab.h>

wchar_t * wcstr = NULL;



//参考地址： http://blog.bitfly.cn/post/mbstowcs-func/
wchar_t * AnsiToUnicode(char * mbstr)
{
	wchar_t * wcstr;
	size_t _size = mbstowcs(NULL, mbstr, 0);
	wcstr = new wchar_t[_size + 1];
	size_t _ret = mbstowcs(wcstr, mbstr, _size + 1);
	if (_ret == -1)
	{
		delete[] wcstr;
		wcstr = NULL;
	}
	return wcstr;
}

int CrEngine::Initialization()
{ 
	if (false == Init())
	{
		return -1;
	}

	wcstr = AnsiToUnicode("ddddddd");

	return 0;
}

int CrEngine::Start(CrScene * pScene)
{
	CrEngine::Director()->InsertScene(pScene);
	CrEngine::Director()->RunScene(pScene);
	m_pInstance->m_isRun = true;
	return m_pInstance->MainLoop(); 
}

void CrEngine::Stop()
{
	m_pInstance->m_isRun = false;
}

CrEngine::CrEngine()
:m_isInit(false)
{
}

CrEngine::~CrEngine()
{

}

bool CrEngine::Init()
{
	if (m_isInit)
		return true;

#ifdef _CR_DEBUG
	printf("log: Initializing GLFW ...\n");
#endif
	if (GL_FALSE == glfwInit()){
#ifdef _CR_DEBUG
		printf("error: GLFW initialization fail\n");	
#endif
		return false;
	}
#ifdef _CR_DEBUG
	printf("log: Initializing Config ...\n");
#endif
	m_pConfig = new CrConfig();
	if (!(m_pConfig && m_pConfig->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: Config initialize fail\n");
#endif
		return false;
	}

#ifdef _CR_DEBUG
	printf("log: Initializing Window ...\n");
#endif
	m_pWindow = new CrWindow();
	if (!(m_pWindow && m_pWindow->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: Window initializing fail\n");
#endif
		return false;
	}

#ifdef _CR_DEBUG
	printf("log: Initializing GLEW ...\n");
#endif
	
	if (glewInit() != GLEW_OK)
	{
#ifdef _CR_DEBUG
		printf("error: GLEW Initializing fail\n");
#endif
		return false;
	}
	
#ifdef _CR_DEBUG
	printf("log: Initializing MemoryPool ...\n");
#endif
	m_pMemoryPool = new CrMemoryPool();
	if (!(m_pMemoryPool && m_pMemoryPool->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: MemoryPool initialize fail\n");
#endif
		return false;
	}

#ifdef _CR_DEBUG
	printf("log: Initializing Director ...\n");
#endif
	m_pDirector = new CrDirector();
	if (!(m_pDirector && m_pDirector->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: Director initialize fail\n");
#endif
		return false;
	}
	
#ifdef _CR_DEBUG
	printf("log: Initialize Time ...\n");
#endif
	m_pTime = new CrTime();
	if (!(m_pTime && m_pTime->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: Time initialize fail\n");
#endif
		return false;
	}
	
#ifdef _CR_DEBUG
	printf("log: Initialize Shader ...\n");
#endif
	
	if (!CrShaderUtility::Instance()->Init())
	{
#ifdef _CR_DEBUG
		printf("error: Shader initialize fail\n");
#endif
		return false;
	}
	
#ifdef _CR_DEBUG
	printf("log: Initialize Event ...\n");
#endif
	m_pEvent = new CrEvent();
	if (!(m_pEvent && m_pEvent->Init()))
	{
#ifdef _CR_DEBUG
		printf("error: Event initialize fail\n");
#endif
		return false;
	}
	

	CrFontLab::Instance()->Init();
	/*
	GLuint m_program = CrShaderMgr::GetInstance()->CreateShader("testShader.vert", "testShader.frag");

	m_pModel = CrModel::CreateCube();//payne
	m_pModel->Retain();//payne

	

	//投影矩阵
	glm::mat4 projection = glm::perspective(45.f, 4.f / 3.f, 1.f, 100.f);

	//视图矩阵
	glm::mat4 view = glm::lookAt(glm::vec3(-0.f, 0.f, -5.f), glm::vec3(-0.f, 0.f, 2.f), glm::vec3(0, 1, 0));


	CrEngineDevice::GetInstance()->SetShader(m_program);
	CrEngineDevice::GetInstance()->SetProjectionMatrix(&projection);
	CrEngineDevice::GetInstance()->SetViewMatrix(&view);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//点大小
	glPointSize(1.f);
	//线宽
	glLineWidth(1.f);
	//正反面
	glFrontFace(GL_CCW);
	//裁剪
	//glCullFace(GL_BACK);
	//开启
	//glEnable(GL_CULL_FACE);
	//渲染模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawArrays(GL_TRIANGLES, 0, 3102);
	r = 15;
	*/


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//点大小
	glPointSize(1.f);
	//线宽
	glLineWidth(2.f);
	//正反面
	glFrontFace(GL_CCW);
	//裁剪
	glCullFace(GL_BACK);
	//开启
	glEnable(GL_CULL_FACE);
	//渲染模式
	glPolygonMode(GL_FRONT, GL_LINE);
	m_isInit = true;

	return true;
}

void CrEngine::OnEnter()
{

}

int CrEngine::MainLoop()
{
	while (m_isRun)
	{
		m_pTime->Update();
		if (m_pTime->IsMeetInterval())
		{
			m_pDirector->Update();

			CrFontLab::Instance()->Render(wcstr, 50, 50, 900, 25);

			m_pWindow->Update();
			m_pEvent->Update();
		}
	}
	Destory();

	return 0;
}

void CrEngine::OnExit()
{

}

void CrEngine::ProMessage(GLFWwindow* window, GLuint64 msg, unsigned __int64 wParam, unsigned __int64 lParam)
{
	m_pEvent->ProMessage(msg, wParam, lParam);
}

void CrEngine::Destory()
{
	//m_pModel->Release();//payne
	m_pMemoryPool->ClearUpMemory();//payne
	glfwTerminate(); 

	delete[] wcstr;
	wcstr = NULL;
}