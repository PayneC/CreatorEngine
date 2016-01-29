/*
CreatorEngine
Class CrScene
Payne
*/

#ifndef _CREATOR_SCENE_H
#define _CREATOR_SCENE_H

#include "CrGameObject.h"
#include <list>

class CrScene : public CrGameObject
{
public:
	static CrScene * Create();
	static CrScene * Create(std::string name);
	
protected:
	CrScene();

public:
	~CrScene();

	virtual void Awake();
	virtual void Awake(std::string name);
protected:
	
};

#endif

/*导演管理 场景 场景存储相机  相机随同普通node逻辑变化  相机负责渲染 相机与被渲染物体之间node加掩码
层用来隔离 不参与遮挡关系的物体
各种形状是基本单位
*/