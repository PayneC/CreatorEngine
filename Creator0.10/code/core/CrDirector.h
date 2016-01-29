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

class CrDirector
{
	friend class CrEngine;
	friend class CrCamera;
	friend class CrModel;
private:
	CrDirector();
	bool Init();
	void Destory();
	void Update();
	void RenderCamera(CrCamera * pCamera);

	void AddCamera(CrCamera * pCamera);
	void AddDrawTarget(CrModel * pModel);

public:
	~CrDirector();

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
	//std::list<CrCamera*>::iterator m_itorCamera;
};

#endif