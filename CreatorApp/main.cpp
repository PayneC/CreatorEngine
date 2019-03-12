/*
Mobius
function
2014/12/22
Payne
*/

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK,__FILE__,__LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#include <CreatorEngine.h>

#include "test.h"
#include "testCamera.h"

void Scene1()
{
	SharedPtr<CrTexture> texture = CrTextureUtility::Instance()->LoadTexture("001.png");

	SharedPtr<CrScene>  pScene = CrGameObject::CreateGameObject<CrScene>("scene");

	SharedPtr<CrGameObject> go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	go->get_transform()->SetParent(pScene->get_transform());	

	go->AddComponent<test>();

	go->get_transform()->SetPosition(glm::vec3(0, 0, 0));
	go->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->get_transform()->SetRotation(glm::vec3(0, 0, 0));
	SharedPtr<CrMeshRender>  meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor("vBaseColor", glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetTexture("diffuse", texture, GL_TEXTURE0, 0);
	//meshRender->GetMaterial()->SetpMainTexture(texture);

	SharedPtr<CrCamera>  pCamera = CrGameObject::CreateGameObject<CrCamera>("Camera");
	pCamera->get_transform()->SetParent(pScene->get_transform());	
	pCamera->get_transform()->SetPosition(glm::fvec3(0.f, 0.f, 20.0f));

	pCamera->get_transform()->LookAt(go);
	pCamera->AddComponent<testCamera>();

	CrCamera::m_pCameraList.push_back(pCamera);

	SharedPtr<CrTexture> texture2 = CrTextureUtility::Instance()->LoadTexture("TexMagic01.png");

	SharedPtr<CrGameObject>  go2 = NULL;
	for (int i = 0; i < 40; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 1; ++k)
			{
				go2 = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_CUBE, "cube");
				go2->get_transform()->SetParent(go->get_transform());				
				//go2->AddComponent<test>();
				go2->get_transform()->SetLocalPosition(glm::vec3(-18 + i * 4, 0.f, 0.f));
				//go2->GetTransform()->SetLocalScale(glm::vec3(1.f, 1.f, 1.f));
				meshRender = go2->GetComponent<CrMeshRender>();
				meshRender->GetMaterial()->SetColor("vBaseColor", glm::vec4((float)i / 10.f, (float)i / 10.f, (float)i / 10.f, 1.f));
				//meshRender->GetMaterial()->SetpMainTexture(texture2);
				meshRender->GetMaterial()->SetTexture("diffuse", texture, GL_TEXTURE0, 0);
			}
		}
	}

	go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");	
	go->get_transform()->SetParent(pScene->get_transform());
	go->get_transform()->SetPosition(glm::vec3(5, -5, 5));
	go->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->get_transform()->SetRotation(glm::vec3(0, 0, 0));
	meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor("vBaseColor", glm::vec4(1, 1, 1, 1));
	//meshRender->GetMaterial()->SetpMainTexture(texture);
	meshRender->GetMaterial()->SetTexture("diffuse", texture, GL_TEXTURE0, 0);

	CrScene::SetCurrentScene(pScene);

	CrEngine::Start();		
}

void Scene2()
{	
	SharedPtr<CrTexture> texture2 = CrTextureUtility::Instance()->LoadTexture("SandyGround.tga");
	SharedPtr<CrTexture> textureN = CrTextureUtility::Instance()->LoadTexture("SandyGround_Normal.tga");

	SharedPtr<CrScene>  pScene = CrGameObject::CreateGameObject<CrScene>("scene");
	
	SharedPtr<CrGameObject>  go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	go->SetParent(pScene);

	go->get_transform()->SetPosition(glm::vec3(0, -1, 0));
	go->get_transform()->SetLocalScale(glm::vec3(50, 1, 50));
	go->get_transform()->SetRotation(glm::vec3(-90, 0, 0));
	SharedPtr<CrMeshRender>  meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor("vBaseColor", glm::vec4(1, 1, 1, 1));
	//meshRender->GetMaterial()->SetpMainTexture(texture2);
	meshRender->GetMaterial()->SetTexture("diffuse", texture2, GL_TEXTURE0, 0);

	SharedPtr<CrGameObject>  go2 = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_SKY_BOX, "skybox");
	go2->SetParent(pScene);

	go2->get_transform()->SetPosition(glm::vec3(0, 0, 0));
	go2->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
	go2->get_transform()->SetRotation(glm::vec3(0, 0, 0));
	go2->AddComponent<test>();
	meshRender = go2->GetComponent<CrMeshRender>();
	//meshRender->GetMaterial()->SetpMainTexture(texture2);
	//meshRender->GetMaterial()->SetpNormalTexture(textureN);

	SharedPtr<CrTexture> cubMap = CrTextureUtility::Instance()->LoadCubMap("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");

 	SharedPtr<CrShader> shader = CrShaderUtility::CreateShader("VertexSkyBox.vert", "VertexSkyBox.frag");
 	meshRender->GetMaterial()->SetShader(shader);
	meshRender->GetMaterial()->SetCubMap("skybox", cubMap, GL_TEXTURE0, 0);	

	SharedPtr<CrGameObject>  go3 = CrMeshUtility::LoadModel("nanosuit.obj");
	go3->SetParent(pScene);

	go3->get_transform()->SetPosition(glm::vec3(-3, -1, 0));
	go3->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
	go3->get_transform()->SetRotation(glm::vec3(0, 0, 0));

	SharedPtr<CrGameObject>  go4 = CrMeshUtility::LoadModel("SitupToIdle.fbx");
	go4->SetParent(pScene);
	go4->get_transform()->SetPosition(glm::vec3(3, -1, 0));
	go4->get_transform()->SetLocalScale(glm::vec3(0.1, 0.1, 0.1));
	go4->get_transform()->SetRotation(glm::vec3(0, 0, 0));


	SharedPtr<CrCamera>  pCamera = CrGameObject::CreateGameObject<CrCamera>("Camera");
	pCamera->SetParent(pScene);
	pCamera->get_transform()->SetPosition(glm::fvec3(0.f, 15.f, 3.0f));
	pCamera->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
	pCamera->get_transform()->SetLocalRotation(glm::vec3(0, 0, 0));
	//pCamera->get_transform()->LookAt(go2);
	pCamera->AddComponent<testCamera>();

	CrCamera::m_pCameraList.push_back(pCamera);

	CrScene::SetCurrentScene(pScene);
}

void Application()
{
	Scene2();
	CrEngine::Start();
}

int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (CrEngine::Initialization() != 0)
		return 0;
	Application();
	_CrtDumpMemoryLeaks();

	return 0;
}