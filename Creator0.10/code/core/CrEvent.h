/*
CreatorEngine
Class CrEvent
Payne
*/

#ifndef _CREATOR_EVENT_H
#define _CREATOR_EVENT_H

#include <glew\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <CrSingleton.h>

class CrEvent : public CrSingleton<CrEvent>
{
public:
	CrEvent();
	~CrEvent();
public:
	bool Init();
	void ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam);
	void Update();
};

#endif