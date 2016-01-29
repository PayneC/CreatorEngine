/*
CreatorEngine
Class CrCamera
Payne
*/

#ifndef _CREATOR_CAMERA_H
#define _CREATOR_CAMERA_H

#include "CrModel.h"

class CrCamera : public CrGameObject
{
	friend class CrDirector;
public:
	static CrCamera * Create();

public:
	CrCamera();
	~CrCamera();

	virtual void Update(float delay);
	void LookAt(CrGameObject * node);
private:

	bool m_isChangeParent;

	std::list<CrModel *> m_pDrawTargets;

	glm::fmat4 m_m4ViewMatrix;
	
};

#endif