#include "CrObject.h"
#include "CrMemoryPool.h"

CrMemoryPool::CrMemoryPool()
	:m_listReleaseMemoryChunk()
{
}

CrMemoryPool::~CrMemoryPool()
{
}

bool CrMemoryPool::Init()
{
	return true;
}

void CrMemoryPool::AddChunkToReleasePool(CrObject * pChunk)
{
	pChunk->Retain();
	m_listReleaseMemoryChunk.push_back(pChunk);
}

void CrMemoryPool::ClearUpMemory()
{
	if (m_listReleaseMemoryChunk.empty())
		return;

	for each (CrObject * pChunk in m_listReleaseMemoryChunk)
	{
		--pChunk->m_sUserNumber;
		if (pChunk && pChunk->m_sUserNumber < 1)
		{
			delete pChunk;
			pChunk = NULL;
		}
	}

	m_listReleaseMemoryChunk.clear();
}

void CrMemoryPool::FreeMemory()
{
	if (m_listReleaseMemoryChunk.empty())
		return;

	for each (CrObject * pChunk in m_listReleaseMemoryChunk)
	{
		if (pChunk)
		{
			delete pChunk;
			pChunk = NULL;
		}
	}

	m_listReleaseMemoryChunk.clear();
}