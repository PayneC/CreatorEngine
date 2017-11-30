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

using namespace CreatorEngine;

void Scene1()
{
	CrTexture * texture = CrTextureUtility::Instance()->LoadTexture("001.png");

	CrScene * pScene = CrObject::Instance<CrScene>();

	CrGameObject * go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	pScene->AddGameObject(go);

	go->AddComponent<test>();

	go->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	go->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	CrMeshRender * meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor(glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetpMainTexture(texture);

	CrCamera * pCamera = CrGameObject::CreateGameObject<CrCamera>("Camera");
	pScene->AddGameObject(pCamera);
	pCamera->GetTransform()->SetPosition(glm::fvec3(0.f, 0.f, 20.0f));

	pCamera->GetTransform()->LookAt(go);
	pCamera->AddComponent<testCamera>();

	CrTexture * texture2 = CrTextureUtility::Instance()->LoadTexture("TexMagic01.png");

	CrGameObject * go2 = NULL;
	for (int i = 0; i < 40; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 1; ++k)
			{
				go2 = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_CUBE, "cube");
				go->AddChild(go2);
				//go2->AddComponent<test>();
				go2->GetTransform()->SetLocalPosition(glm::vec3(-18 + i * 4, 0.f, 0.f));
				//go2->GetTransform()->SetLocalScale(glm::vec3(1.f, 1.f, 1.f));
				meshRender = go2->GetComponent<CrMeshRender>();
				meshRender->GetMaterial()->SetColor(glm::vec4((float)i / 10.f, (float)i / 10.f, (float)i / 10.f, 1.f));
				meshRender->GetMaterial()->SetpMainTexture(texture2);
			}
		}
	}

	go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	pScene->AddGameObject(go);
	go->GetTransform()->SetPosition(glm::vec3(5, -5, 5));
	go->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor(glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetpMainTexture(texture);

	UICanvas * canvas = CrGameObject::CreateGameObject<UICanvas>("canvas");
	canvas->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	canvas->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	canvas->GetTransform()->SetRotation(glm::vec3(0, 0, 0));

	CrTexture * texture3 = CrTextureUtility::Instance()->LoadTexture("zhongxin.png");

	UISprite * sprite = CrGameObject::CreateGameObject<UISprite>(EPresetMeshType::CR_MESH_TYPE_QUAD, "sprite");
	canvas->AddChild(sprite);

	sprite->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	sprite->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	sprite->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	meshRender = sprite->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetpMainTexture(texture3);


	CrScene::SetCurrentScene(pScene);

	CrEngine::Start();
}

void Scene2()
{	
	CrTexture * texture2 = CrTextureUtility::Instance()->LoadTexture("SandyGround.tga");
	CrTexture * textureN = CrTextureUtility::Instance()->LoadTexture("SandyGround_Normal.tga");

	CrScene * pScene = CrObject::Instance<CrScene>();
	
	CrGameObject * go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	pScene->AddGameObject(go);
	go->GetTransform()->SetPosition(glm::vec3(0, -1, 0));
	go->GetTransform()->SetLocalScale(glm::vec3(50, 1, 50));
	go->GetTransform()->SetRotation(glm::vec3(-90, 0, 0));
	CrMeshRender * meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor(glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetpMainTexture(texture2);

	CrGameObject * go2 = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_CUBE, "cube");
	pScene->AddGameObject(go2);
	go2->GetTransform()->SetPosition(glm::vec3(0, 1, 0));
	go2->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go2->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	go2->AddComponent<test>();
	meshRender = go2->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetpMainTexture(texture2);
	meshRender->GetMaterial()->SetpNormalTexture(textureN);

	CrGameObject * go3 = CrMeshUtility::LoadModel("nanosuit.obj");
	pScene->AddGameObject(go3);
	go3->GetTransform()->SetPosition(glm::vec3(0, -1, 0));
	go3->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go3->GetTransform()->SetRotation(glm::vec3(0, 0, 0));


	CrCamera * pCamera = CrGameObject::CreateGameObject<CrCamera>("Camera");
	pScene->AddGameObject(pCamera);
	pCamera->GetTransform()->SetPosition(glm::fvec3(0.f, 15.f, 3.0f));
	pCamera->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	pCamera->GetTransform()->SetLocalRotation(glm::vec3(1, 1, 1));
	//pCamera->GetTransform()->LookAt(go2);
	pCamera->AddComponent<testCamera>();

	CrScene::SetCurrentScene(pScene);

	CrEngine::Start();
}

void Application()
{
	Scene2();
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