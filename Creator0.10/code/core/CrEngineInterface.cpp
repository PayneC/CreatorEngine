#include "CrEngineInterface.h"

using namespace CreatorEngine;

int CreatorEngine::InitEngine()
{
	return CrEngine::CreatorAwake() ? 0 : 1;
}

int CreatorEngine::CloseEngine()
{
	CrEngine::Stop();
	return 0;
}