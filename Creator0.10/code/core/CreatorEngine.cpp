#include "CreatorEngine.h"

int CreatorEngine::Initialization()
{
	int result = CrEngine::Instance()->Initialization();
	return result;
}

int CreatorEngine::Start(CrScene * pScene)
{
	int result = CrEngine::Instance()->Start(pScene);
	return result;
}

void CreatorEngine::Stop()
{
	CrEngine::Instance()->Stop();
}