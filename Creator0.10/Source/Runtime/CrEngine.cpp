#include <CrEngine.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

void _Render(CrGameObject * pGameObject, CrCamera * pCamera)
{
	if (pGameObject == NULL || !pGameObject->GetActive())
		return;

	CrMeshRender * meshRender = pGameObject->GetComponent<CrMeshRender>();
	CrTransform * transform = pGameObject->GetTransform();
	if (meshRender != NULL && transform != NULL)
	{
		glm::mat4 mvp = pCamera->GetVP() * transform->GetLocalToWorldMatrix();
		glm::mat4 v = pCamera->GetTransform()->GetWorldToLocalMatrix();
		glm::mat4 m = transform->GetLocalToWorldMatrix();

		meshRender->Draw(mvp, pCamera->GetTransform()->GetPosition(), m, v);
	}

	std::vector<CrGameObject * > gameobjects = pGameObject->GetChildren();

	std::vector<CrGameObject * >::iterator iter = gameobjects.begin();
	std::vector<CrGameObject * >::iterator iterEnd = gameobjects.end();

	CrGameObject * gameobject = NULL;
	for (; iter != iterEnd; ++iter)
	{
		gameobject = (*iter);
		_Render(gameobject, pCamera);
	}
}

int CrEngine::Initialization()
{
	if (false == Init())
	{
		return -1;
	}
	return 0;
}

int CrEngine::Start()
{
	ImGui_ImplGlfwGL3_Init(CrWindow::GetEngineWindow(), false);
	m_isInit = true;

	m_isRun = true;	
	while (m_isRun)
	{
		MainLoop();
	}
	Destory();
	return 0;
}

void CrEngine::Stop()
{
	m_isRun = false;
}

bool CrEngine::Init()
{
	if (m_isInit)
		return true;

#ifdef _DEBUG
	printf("log: Initializing GLFW ...\n");
#endif
	if (GL_FALSE == glfwInit()) {
#ifdef _DEBUG
		printf("error: GLFW initialization fail\n");
#endif
		return false;
	}

#ifdef _DEBUG
	printf("log: Initializing Window ...\n");
#endif
	if (!(CrWindow::Create()))
	{
#ifdef _DEBUG
		printf("error: Window initializing fail\n");
#endif
		return false;
	}

#ifdef _DEBUG
	printf("log: Initializing GLEW ...\n");
#endif

	if (glewInit() != GLEW_OK)
	{
#ifdef _DEBUG
		printf("error: GLEW Initializing fail\n");
#endif
		return false;
	}

#ifdef _DEBUG
	printf("log: Initializing Director ...\n");
#endif

#ifdef _DEBUG
	printf("log: Initialize Time ...\n");
#endif

	if (!(CrTime::Instance()->Init()))
	{
#ifdef _DEBUG
		printf("error: Time initialize fail\n");
#endif
		return false;
	}

#ifdef _DEBUG
	printf("log: Initialize Shader ...\n");
#endif

	if (!CrShaderUtility::Instance()->Init())
	{
#ifdef _DEBUG
		printf("error: Shader initialize fail\n");
#endif
		return false;
	}

	glEnable(GL_TEXTURE_2D);
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
	//glEnable(GL_CULL_FACE);
	//渲染模式
	//glPolygonMode(GL_FRONT, GL_LINE);

	return true;
}

void CrEngine::OnEnter()
{

}

void DrawObjectTree(CrGameObject * _go)
{
	if (ImGui::TreeNode(_go->GetName().c_str()))
	{
		std::vector<CrGameObject * > _childs = _go->GetChildren();
		std::vector<CrGameObject * >::iterator iter = _childs.begin();
		std::vector<CrGameObject * >::iterator iterEnd = _childs.end();
		for (; iter != iterEnd; ++iter)
		{
			DrawObjectTree((*iter));
		}
		ImGui::TreePop();
	}
}

void DrawSceneTree(CrScene * _go)
{
	std::vector<CrGameObject * > _childs = _go->GetChildren();
	std::vector<CrGameObject * >::iterator iter = _childs.begin();
	std::vector<CrGameObject * >::iterator iterEnd = _childs.end();
	for (; iter != iterEnd; ++iter)
	{
		DrawObjectTree((*iter));
	}
}

int CrEngine::MainLoop()
{
	CrTime::Instance()->Update();
	if (CrTime::Instance()->IsMeetInterval())
	{
		Event::Update();

		ImGui_ImplGlfwGL3_NewFrame();

		CrScene * scene = CrScene::CurrentScene();
		if (scene)
		{
			scene->Update(CrTime::Instance()->GetDelateTimeLF());

			std::list<CrCamera*> cameras = CrCamera::AllCamera();
			if (cameras.size() > 0)
			{
				std::list<CrCamera*>::iterator cameraIter = cameras.begin();
				std::list<CrCamera*>::iterator cameraIterEnd = cameras.end();
				CrCamera * camera = NULL;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0, 0, 0, 1);

				glEnable(GL_DEPTH_TEST);

				for (; cameraIter != cameraIterEnd; ++cameraIter)
				{
					camera = (*cameraIter);
					ImGui::Begin("camera");
					glm::vec3 pos = camera->GetTransform()->GetPosition();
					ImGui::Text("position %f %f %f", pos.x, pos.y, pos.z);
					glm::vec3 rot = camera->GetTransform()->GetRotation();
					ImGui::Text("rotation %f %f %f", rot.x, rot.y, rot.z);
					ImGui::End();

					std::vector<CrGameObject * > gameobjects = scene->GetChildren();
					std::vector<CrGameObject * >::iterator iter = gameobjects.begin();
					std::vector<CrGameObject * >::iterator iterEnd = gameobjects.end();

					CrGameObject * gameobject = NULL;
					for (; iter != iterEnd; ++iter)
					{
						gameobject = (*iter);
						_Render(gameobject, camera);
					}
				}

				glDisable(GL_DEPTH_TEST);
			}

			std::list<UICanvas*> canvases = UICanvas::AllCanvas();
			if (canvases.size() > 0)
			{
				std::list<UICanvas*>::iterator canvasIter = canvases.begin();
				std::list<UICanvas*>::iterator canvasIterEnd = canvases.end();
				UICanvas * canvas = NULL;

				for (; canvasIter != canvasIterEnd; ++canvasIter)
				{
					canvas = (*canvasIter);
					canvas->Render();
				}
			}

			unsigned int _fps = CrTime::Instance()->GetFramesPerSecond();
		}
	
		ImGui::Text("Hello, world!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (scene)
		{
			DrawSceneTree(scene);
		}
		if (ImGui::Button("exit"))
		{
			Stop();
		}

		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(CrWindow::GetEngineWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui::Render();

		//内存泄漏飞起的地方
		//CrFontLab::Instance()->Render(wcstr, 50, 50, 900, 25);

		glfwSwapBuffers(CrWindow::GetEngineWindow());
	}

	return 0;
}

void CrEngine::OnExit()
{

}

void CrEngine::Destory()
{
	Event::Clear();
	CrObject::FreeObjects();//payne
	glfwTerminate();
}

bool CrEngine::m_isRun(false);
bool CrEngine::m_isInit(false);;
double CrEngine::m_lfTotalDelay(0);