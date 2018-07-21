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
	static std::shared_ptr<TReturnType> Instance();
protected:
	CrObject();
	virtual ~CrObject() = 0;

	std::string m_name;
public:
	std::string get_name() { return m_name; }
	void set_name(std::string name) { m_name = name; }
};

template<typename TReturnType>
std::shared_ptr<TReturnType> CrObject::Instance()
{
	static_assert(std::is_base_of<CrObject, TReturnType>::value, "'T' template parameter to FindComponentByClass must be derived from CrObject");
	std::shared_ptr<TReturnType> _instance = std::make_shared<TReturnType>();
	return _instance;
}

#endif