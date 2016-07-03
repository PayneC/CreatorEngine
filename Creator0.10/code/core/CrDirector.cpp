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
	if (m_pRunScene)
	{
		m_pRunScene->Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for each (CrCamera * var in m_pCameraList)
		{
			m_pRunScene->Render(var->GetVP());
		}
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

void CrDirector::RemoveCamera(CrCamera * pCamera)
{
	m_pCameraList.remove(pCamera);
}