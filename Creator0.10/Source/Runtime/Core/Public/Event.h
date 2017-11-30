/*
CreatorEngine
Class CrEvent
Payne
*/

#ifndef _CREATOR_EVENT_H
#define _CREATOR_EVENT_H

#include <CrObject.h>

typedef void(CrObject::*EventFunc)(GLint64 msg, GLint64 wParam, GLint64 lParam);
struct EventListenEntry
{
public:
	EventFunc func;
	CrObject * object;
};
#define Func_Event(FUN) (EventFunc)(&FUN)

static class DLL_ClASS Event
{
public:
	static void ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam);
	static void Update();
	static void AddListen(CrObject * object, EventFunc func);
	static void RemoveListen(CrObject * object, EventFunc func);
	static void Clear();
private:
	static std::vector <EventListenEntry *> m_eventListenEntrys;
};

#endif