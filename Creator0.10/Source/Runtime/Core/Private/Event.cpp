#include <Event.h>

void Event::Clear()
{
	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (; iter != iterEnd; ++iter)
	{
		entry = (*iter);		
		delete(entry);
	}
	m_eventListenEntrys.clear();
}

void Event::ProMessage(GLint64 msg, GLint64 wParam, GLint64 lParam)
{
	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (;iter != iterEnd; ++iter)
	{
		entry = (*iter);
		((entry->object)->*(entry->func))(msg, wParam, lParam);
	}
}

void Event::Update()
{
	glfwPollEvents();
}

void Event::AddListen(CrObject * object, EventFunc func)
{
	EventListenEntry * entry = new EventListenEntry();
	entry->object = object;
	entry->func = func;
	m_eventListenEntrys.push_back(entry);
}

void Event::RemoveListen(CrObject * object, EventFunc func)
{
	std::vector <EventListenEntry *>::iterator iter = m_eventListenEntrys.begin();
	std::vector <EventListenEntry *>::iterator iterEnd = m_eventListenEntrys.end();

	EventListenEntry * entry = NULL;
	for (; iter != iterEnd; ++iter)
	{
		entry = (*iter);
		if (entry->object == object && entry->func == func)
		{
			m_eventListenEntrys.erase(iter);
			delete(entry);
			break;
		}
	}
}

std::vector <EventListenEntry *> Event::m_eventListenEntrys;