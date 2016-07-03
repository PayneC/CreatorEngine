/*
CreatorEngine
Class CrDirector
Payne
*/

#ifndef _CREATOR_DIRECTOR_H
#define _CREATOR_DIRECTOR_H

#include <map>
#include <string>
#include "CrCamera.h"
#include "CrScene.h"
#include <CrSingleton.h>

class CrDirector : public CrSingleton<CrDirector>
{
	friend class CrCamera;
	friend class CrModel;

public:
	CrDirector();
	~CrDirector();

	void Destory();
	void RenderCamera(CrCamera * pCamera);
	void AddCamera(CrCamera * pCamera);
	void RemoveCamera(CrCamera * pCamera);

	bool Init();
	void Update();
	void InsertScene(CrScene * pScene);

	void Remove(std::string name);
	void Remove(CrScene * pScene);

	void RemoveAll();

	void RunScene(std::string name);
	void RunScene(CrScene * pScene);
	void SetFps(unsigned int FPS);
	
private:
	std::map<std::string, CrScene*> m_pScenes;
	std::map<std::string, CrScene*>::iterator m_itorScene;
	CrScene * m_pRunScene;

	std::list<CrCamera*> m_pCameraList;
};

#endif