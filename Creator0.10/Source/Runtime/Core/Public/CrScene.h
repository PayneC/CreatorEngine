/*
CreatorEngine
Class CrScene
Payne
*/

#ifndef _CREATOR_SCENE_H
#define _CREATOR_SCENE_H

#include <CrGameObject.h>

class DLL_ClASS CrScene : public CrObject
{
public:
	static CrScene * CurrentScene();
	static void SetCurrentScene(CrScene * var);

public:
	CrScene();
	~CrScene();

	void AddGameObject(CrGameObject * gameobject);
	void RemoveGameObject(CrGameObject * gameobject);
	const std::vector<CrGameObject *> GetChildren() const { return m_pChildren; }
	void Update(double dt);

protected:
	static CrScene * m_pRunScene;

	std::vector<CrGameObject *> m_pChildren;
};

#endif