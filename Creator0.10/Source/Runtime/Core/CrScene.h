/*
CreatorEngine
Class CrScene
Payne
*/

#ifndef _CREATOR_SCENE_H
#define _CREATOR_SCENE_H

#include <Core/CrGameObject.h>
#include <list>

class DLL_ClASS CrScene : public CrGameObject
{
public:
	CrScene();
	~CrScene();
protected:
	
};

#endif

/*导演管理 场景 场景存储相机  相机随同普通node逻辑变化  相机负责渲染 相机与被渲染物体之间node加掩码
层用来隔离 不参与遮挡关系的物体
各种形状是基本单位
*/