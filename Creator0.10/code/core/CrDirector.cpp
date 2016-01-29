#include "CrDirector.h"
#include "CrEngine.h"

CrDirector::CrDirector()
{
}

CrDirector::~CrDirector()
{

}

bool CrDirector::Init()
{
	m_pScenes = std::map<std::string, CrScene*>();
	m_pCameraList = std::list<CrCamera*>();
	return true;
}

void CrDirector::Destory()
{

}

void CrDirector::Update()
{
	m_pCameraList.clear();
	if (m_pRunScene)
	{
		m_pRunScene->Update(CrEngine::Time()->GetDelateTime());//执行 变化并且 遍历所有相机
		for each (CrCamera * var in m_pCameraList)
		{
			var->m_pDrawTargets.clear();
		}
		m_pRunScene->Render();		//挑选需要渲染的部分

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//绘制逻辑
		for each (CrCamera * var in m_pCameraList)
		{
			RenderCamera(var);
		}
	}
}

void CrDirector::RenderCamera(CrCamera * pCamera)
{
	CrEngine::Render()->SetViewMatrix(&pCamera->m_m4ViewMatrix);
	for each (CrModel * var in pCamera->m_pDrawTargets)
	{
		CrEngine::Render()->Draw(var);
	}
	
}

void CrDirector::InsertScene(CrScene * pScene)
{
	if (pScene)
	{
		m_pScenes.insert(std::pair<std::string, CrScene *>(pScene->GetName(), pScene));
		pScene->Retain();
	}
}

void CrDirector::Remove(std::string name)
{
	m_itorScene = m_pScenes.find(name);
	if (m_itorScene == m_pScenes.end())
		return;

	m_itorScene->second->Release();
	m_pScenes.erase(m_itorScene);
}

void CrDirector::Remove(CrScene * pScene)
{
	m_itorScene = m_pScenes.find(pScene->GetName());
	if (m_itorScene == m_pScenes.end())
		return;

	m_itorScene->second->Release();
	m_pScenes.erase(m_itorScene);
}

void CrDirector::RemoveAll()
{
	for (m_itorScene; m_itorScene != m_pScenes.end(); ++m_itorScene)
	{
		m_itorScene->second->Release();
	}

	m_pScenes.clear();
}

void CrDirector::RunScene(std::string name)
{
	m_itorScene = m_pScenes.find(name);
	if (m_itorScene == m_pScenes.end())
		return;

	if (m_pRunScene){
		m_pRunScene->Release();
	}
	m_pRunScene = m_itorScene->second;
	m_pRunScene->Retain();
}

void CrDirector::RunScene(CrScene * pScene)
{
	if (!pScene)
		return;

	if (m_pRunScene){
		m_pRunScene->Release();
	}
	m_pRunScene = pScene;
	m_pRunScene->Retain();
}

void CrDirector::SetFps(unsigned int FPS)
{
	CrEngine::Time()->SetFramesPerSecond(FPS);
}

//相机由导演管理
//相机父节点变了之后 电泳导演类的 相机检测 如果自己 在当前场景 则加到 导演类的相机列表

void CrDirector::AddCamera(CrCamera * pCamera)
{
	m_pCameraList.push_back(pCamera);
}

void CrDirector::AddDrawTarget(CrModel * pModel)
{
	for each (CrCamera * var in m_pCameraList)
	{
		if (true)//检测 是否在视锥体内
			var->m_pDrawTargets.push_back(pModel);
	}
}

//遍历所有的场景物件
//判断需要绘制的物件