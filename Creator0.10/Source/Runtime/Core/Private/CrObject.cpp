#include <CrObject.h>


std::vector<CrObject*> CrObject::m_objects;

void CrObject::ClearUpObjects()
{
	if (m_objects.empty())
		return;

	std::vector<CrObject*>::iterator iter = m_objects.begin();
	std::vector<CrObject*>::iterator iterEnd = m_objects.end();
	CrObject * pChunk = NULL;
	for (; iter != iterEnd; )
	{
		pChunk = (*iter);
		if (pChunk && pChunk->UserCount() == 0)
		{
			delete pChunk;
			m_objects.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CrObject::FreeObjects()
{
	if (m_objects.empty())
		return;

	std::vector<CrObject*>::iterator iter = m_objects.begin();
	std::vector<CrObject*>::iterator iterEnd = m_objects.end();

	CrObject * pChunk = NULL;
	for (; iter != iterEnd; ++iter)
	{
		pChunk = (*iter);
		if (pChunk)
		{
			delete pChunk;
		}
	}
	m_objects.clear();
}

CrObject::CrObject()
:m_sUserNumber(0)
{
	m_objects.push_back(this);
}

CrObject::~CrObject()
{
}

void CrObject::Release()
{
	--m_sUserNumber;
}
void CrObject::Retain()
{
	++m_sUserNumber;
}