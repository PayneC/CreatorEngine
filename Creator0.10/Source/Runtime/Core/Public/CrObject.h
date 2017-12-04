/*
CreatorEngine
Class CrObject
Payne
*/

#ifndef _CREATOR_OBJECT_H
#define _CREATOR_OBJECT_H

#include <CrDefine.h>

class DLL_ClASS CrObject
{
public:
	template<typename TReturnType>
	//static std::shared_ptr<TReturnType> Instance();
	static TReturnType* Instance();

	static std::vector<CrObject*> m_objects;

	static void ClearUpObjects();
	static void FreeObjects();
protected:
	CrObject();
	virtual ~CrObject() = 0;

public:
	void Release();
	void Retain();
	
	unsigned short UserCount(){ return m_sUserNumber; }
protected:
	unsigned short m_sUserNumber;
};

template<typename TReturnType>
TReturnType* CrObject::Instance()
{
	static_assert(std::is_base_of<CrObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrObject");

	//std::shared_ptr<TReturnType> _instance = std::make_shared<TReturnType>();
	TReturnType * _instance = new TReturnType();
	return _instance;
}
#endif