/*
CreatorEngine
Class CrObject
Payne
*/

#ifndef _CREATOR_OBJECT_H
#define _CREATOR_OBJECT_H

#include <CrDefine.h>
#include <CrMemoryPool.h>

class DLL_ClASS CrObject
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

template<typename TReturnType>
TReturnType * CrObject::Instance()
{
	static_assert(std::is_base_of<CrObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrObject");

	TReturnType * _instance = new TReturnType();
	return _instance;
}
#endif