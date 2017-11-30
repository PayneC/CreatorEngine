#include <CrScene.h>

CrScene::CrScene()
{

}

CrScene::~CrScene()
{
}

void CrScene::AddGameObject(CrGameObject * gameobject)
{
	m_pChildren.push_back(gameobject);
	gameobject->Retain();
}

void CrScene::RemoveGameObject(CrGameObject * gameobject)
{
	if (!gameobject)
		return;

	std::vector<CrGameObject * >::iterator iter = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == gameobject)
			break;
	}
	if (iter != iterEnd)
	{
		m_pChildren.erase(iter);
		gameobject->Release();
	}
}

void CrScene::Update(double dt)
{
	std::vector<CrGameObject * >::iterator iter = m_pChildren.begin();
	std::vector<CrGameObject * >::iterator iterEnd = m_pChildren.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(dt);
	}
}

CrScene * CrScene::m_pRunScene = NULL;

CrScene * CrScene::CurrentScene()
{
	return m_pRunScene;
}
void CrScene::SetCurrentScene(CrScene * var)
{
	m_pRunScene = var;
}