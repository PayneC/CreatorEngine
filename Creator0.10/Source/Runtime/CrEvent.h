/*
CreatorEngine
Class CrEvent
Payne
*/

#ifndef _CREATOR_EVENT_H
#define _CREATOR_EVENT_H

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <CrSingleton.h>

#include <Core/CrObject.h>

class CrEvent : public CrSingleton<CrEvent>
{
public:
	CrEvent();
	~CrEvent();
public:
	bool Init();
	void ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam);
	void Update();

	void _AddListen(EventListenEntry * entry);

	void AddListen(CrObject * object, EventFunc func);
	void RemoveListen(CrObject * object, EventFunc func);
private:
	std::vector <EventListenEntry *> m_eventListenEntrys;
	double m_mousePosX;
	double m_mousePosY;
	bool m_isInit;
};

#endif