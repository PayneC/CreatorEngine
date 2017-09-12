/*
CreatorEngine
Class CrMemoryPool : CrSingleton
Payne
*/

#ifndef _CREATOR_MEMORYPOOL_H
#define _CREATOR_MEMORYPOOL_H

#include <CrObject.h>
#include <list>
#include <CrSingleton.h>

class DLL_ClASS CrMemoryPool : public CrSingleton<CrMemoryPool>
{
	friend class CrEngine;
private:
	bool Init();
	void Destory();
	void ClearUpMemory();
	void FreeMemory();
public:
	CrMemoryPool();
	~CrMemoryPool();

	void AddChunkToReleasePool(CrObject * pChunk);
	
private:
	std::list<CrObject*> m_listReleaseMemoryChunk;
	std::list<CrObject*>::iterator m_iter;
};

#endif