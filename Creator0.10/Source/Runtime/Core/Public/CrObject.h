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
	static SharedPtr<TReturnType> Instance();
protected:
	CrObject();
	virtual ~CrObject() = 0;

	CEString m_name;
public:
	CEString get_name() { return m_name; }
	void set_name(CEString name) { m_name = name; }
};

template<typename TReturnType>
SharedPtr<TReturnType> CrObject::Instance()
{
	static_assert(std::is_base_of<CrObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrObject");
	SharedPtr<TReturnType> _instance = std::make_shared<TReturnType>();
	return _instance;
}

#endif