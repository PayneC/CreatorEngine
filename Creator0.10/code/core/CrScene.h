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

/*���ݹ��� ���� �����洢���  �����ͬ��ͨnode�߼��仯  ���������Ⱦ ����뱻��Ⱦ����֮��node������
���������� �������ڵ���ϵ������
������״�ǻ�����λ
*/