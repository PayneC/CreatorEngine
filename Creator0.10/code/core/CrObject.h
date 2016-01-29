/*
CreatorEngine
Class CrMemoryChunk
Payne
*/

#ifndef _CREATOR_OBJECT_H
#define _CREATOR_OBJECT_H

#include "CrDefine.h"

class CrObject
{
	friend class CrMemoryPool;

public:
	template<typename TClassType>
	static TClassType * Instance();

protected:
	CrObject();
	virtual ~CrObject() = 0;
	void AutoRelease();

public:
	void Release();
	void Retain();
	
	unsigned short GetUserNumber(){ return m_sUserNumber; }
protected:
	unsigned short m_sUserNumber;
};

template<typename TClassType>
TClassType * CrObject::Instance()
{
	static_assert(is_base_of<CrObject, TClassType>::value, "");

	TClassType * _instance = new TClassType();
	_instance->AutoRelease();
	return _instance;
}

#endif