/*
CreatorEngine
Class CrTransform
Payne
*/

#ifndef _CREATOR_COMPONENT_H
#define _CREATOR_COMPONENT_H

#include <CrObject.h>

class DLL_ClASS IBehaviour
{
public:
	virtual void Start() = 0;
	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt) = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;
	//virtual void OnGUI() = 0;
	//virtual void OnInspectionGUI() = 0;
};

class CrGameObject;
class DLL_ClASS CrComponent : public CrObject, public IBehaviour
{
protected:
	CrComponent();
	~CrComponent();

public:
	virtual void Start();
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

	//virtual void OnGUI();
	//virtual void OnInspectionGUI();

	CrGameObject * GetGameObject();

	//virtual int GetInstanceCountLimit();

	void SetGameObject(CrGameObject * pointer);

protected:
	CrGameObject * m_pGameObject;
};

#endif