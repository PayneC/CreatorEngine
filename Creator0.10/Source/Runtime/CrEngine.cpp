#include <CrEngine.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>


void _Render(SharedPtr<CrGameObject> pGameObject, SharedPtr<CrCamera> pCamera)
{
	if (pGameObject == NULL || !pGameObject->GetActive())
		return;

	SharedPtr<CrMeshRender> meshRender = pGameObject->GetComponent<CrMeshRender>();
	SharedPtr <CrTransform> transform = pGameObject->get_transform();
	if (meshRender != NULL && transform != NULL)
	{
		glm::mat4 mvp = pCamera->GetVP() * transform->GetLocalToWorldMatrix();
		glm::mat4 v = pCamera->get_transform()->GetWorldToLocalMatrix();
		glm::mat4 m = transform->GetLocalToWorldMatrix();

		meshRender->Draw(mvp, pCamera->get_transform()->GetPosition(), m, v);
	}

	std::vector<SharedPtr<CrTransform>> transforms = transform->get_children();
	std::vector<SharedPtr<CrTransform>>::iterator iter = transforms.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = transforms.end();

	for (; iter != iterEnd; ++iter)
	{
		transform = (*iter);
		_Render(transform->GetGameObject(), pCamera);
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

void DrawObjectTree(SharedPtr<CrGameObject> _go)
{
	if (ImGui::TreeNode(_go->get_name().c_str()))
	{
		std::vector<SharedPtr<CrTransform>> _childs = _go->get_transform()->get_children();
		std::vector<SharedPtr<CrTransform>>::iterator iter = _childs.begin();
		std::vector<SharedPtr<CrTransform>>::iterator iterEnd = _childs.end();
		for (; iter != iterEnd; ++iter)
		{
			DrawObjectTree((*iter)->GetGameObject());
		}
		ImGui::TreePop();
	}
}

void DrawSceneTree(SharedPtr<CrScene> _go)
{
	std::vector<SharedPtr<CrTransform>> _childs = _go->get_transform()->get_children();
	std::vector<SharedPtr<CrTransform>>::iterator iter = _childs.begin();
	std::vector<SharedPtr<CrTransform>>::iterator iterEnd = _childs.end();
	for (; iter != iterEnd; ++iter)
	{
		DrawObjectTree((*iter)->GetGameObject());
	}
}

int CrEngine::MainLoop()
{
	CrTime::Instance()->Update();
	if (CrTime::Instance()->IsMeetInterval())
	{
		Event::Update();

		ImGui_ImplGlfwGL3_NewFrame();

		SharedPtr<CrScene> scene = CrScene::CurrentScene();
		if (scene)
		{
			scene->Update(CrTime::Instance()->GetDelateTimeLF());

			std::list<SharedPtr<CrCamera>> cameras = CrCamera::AllCamera();
			if (cameras.size() > 0)
			{
				std::list<SharedPtr<CrCamera>>::iterator cameraIter = cameras.begin();
				std::list<SharedPtr<CrCamera>>::iterator cameraIterEnd = cameras.end();
				SharedPtr<CrCamera> camera = NULL;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0, 0, 0, 1);

				glEnable(GL_DEPTH_TEST);

				for (; cameraIter != cameraIterEnd; ++cameraIter)
				{
					camera = (*cameraIter);
					ImGui::Begin("camera");
					glm::vec3 pos = camera->get_transform()->GetPosition();
					ImGui::Text("position %f %f %f", pos.x, pos.y, pos.z);

					glm::vec3 rot = camera->get_transform()->GetRotation();
					ImGui::Text("rotation %f %f %f", rot.x, rot.y, rot.z);
					
					glm::vec3 scal = camera->get_transform()->GetScale();
					ImGui::Text("scale %f %f %f", scal.x, scal.y, scal.z);

					glm::vec3 lpos = camera->get_transform()->GetLocalPosition();
					ImGui::Text("localPosition %f %f %f", lpos.x, lpos.y, lpos.z);

					glm::vec3 lrot = camera->get_transform()->GetLocalRotation();
					ImGui::Text("localRotation %f %f %f", lrot.x, lrot.y, lrot.z);

					glm::vec3 lscal = camera->get_transform()->GetLocalScale();
					ImGui::Text("localScale %f %f %f", lscal.x, lscal.y, lscal.z);

					glm::quat q = camera->get_transform()->GetQuaternion();
					ImGui::Text("quaternion %f %f %f %f", q.x, q.y, q.z, q.w);

					glm::quat lq = camera->get_transform()->GetLocalQuaternion();
					ImGui::Text("localQuaternion %f %f %f %f", lq.x, lq.y, lq.z, lq.w);

					ImGui::End();

					std::vector<SharedPtr<CrTransform>> transforms = scene->get_transform()->get_children();
					std::vector<SharedPtr<CrTransform>>::iterator iter = transforms.begin();
					std::vector<SharedPtr<CrTransform>>::iterator iterEnd = transforms.end();

					SharedPtr<CrTransform>transform = NULL;
					for (; iter != iterEnd; ++iter)
					{
						transform = (*iter);
						_Render(transform->GetGameObject(), camera);
					}
				}

				glDisable(GL_DEPTH_TEST);
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
	glfwTerminate();
}

bool CrEngine::m_isRun(false);
bool CrEngine::m_isInit(false);;
double CrEngine::m_lfTotalDelay(0);
