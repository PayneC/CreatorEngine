/*
CreatorEngine
Class CrScene
Payne
*/

#ifndef _CREATOR_SCENE_H
#define _CREATOR_SCENE_H

#include <CrGameObject.h>

class DLL_ClASS CrScene : public CrGameObject
{
public:
	static std::shared_ptr<CrScene>  CurrentScene();
	static void SetCurrentScene(std::shared_ptr<CrScene>  var);	
public:
	CrScene();
	~CrScene();	

protected:
	static std::shared_ptr<CrScene>  m_pRunScene;	
};

#endif