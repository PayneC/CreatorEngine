#include "CrScene.h"

CrScene * CrScene::Create()
{
	CrScene * pRef = new CrScene();
	if (!pRef)
	{
		CR_SAFE_DELETE(pRef);
	}
	pRef->Awake();
	return pRef;
}

CrScene * CrScene::Create(std::string name)
{
	CrScene * pRef = new CrScene();
	if (!pRef)
	{
		CR_SAFE_DELETE(pRef);
	}
	pRef->Awake(name);
	return pRef;
}

CrScene::CrScene()
{
	
}

CrScene::~CrScene()
{
}

void CrScene::Awake()
{

}

void CrScene::Awake(std::string name)
{
	m_sName = name;
}

