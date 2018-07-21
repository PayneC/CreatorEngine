#include <CrScene.h>

CrScene::CrScene()
{

}

CrScene::~CrScene()
{
}

std::shared_ptr<CrScene>  CrScene::m_pRunScene = NULL;

std::shared_ptr<CrScene>  CrScene::CurrentScene()
{
	return m_pRunScene;
}
void CrScene::SetCurrentScene(std::shared_ptr<CrScene>  var)
{
	m_pRunScene = var;
}