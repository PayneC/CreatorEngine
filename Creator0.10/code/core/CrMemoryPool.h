/*
CreatorEngine
Class CrMemoryPool : CrSingleton
Payne
*/

#ifndef _CREATOR_MEMORYPOOL_H
#define _CREATOR_MEMORYPOOL_H

#include "CrObject.h"
#include <list>

class CrMemoryPool
{
	friend class CrEngine;
private:
	CrMemoryPool();

	bool Init();
	void Destory();
	void ClearUpMemory();

public:
	~CrMemoryPool();

	void AddChunkToReleasePool(CrObject * pChunk);
	
private:
	std::list<CrObject*> m_listReleaseMemoryChunk;
	std::list<CrObject*>::iterator m_iter;
};

#endif