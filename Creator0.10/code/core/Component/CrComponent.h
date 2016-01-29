/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_COMPONENT_H
#define _CREATOR_COMPONENT_H

#include <CrObject.h>

class CrGameObject;
class CrComponent : public CrObject
{
	friend class CrGameObject;
private:
	void SetGameObject(CrGameObject * pointer);


protected:
	CrComponent();
	~CrComponent();

public:

// 	virtual void Awake();
// 	virtual void OnEnable();
// 	virtual void OnDisable();
// 	virtual void Update(float dt);
// 	virtual void LateUpdate(float dt);
// 	virtual void FixedUpdate(float dt);
// 	virtual void Destroy();
	
	CrGameObject * GetGameObject();

	virtual int GetInstanceCountLimit();

protected:
	CrGameObject * m_pGameObject;
	
};

#endif