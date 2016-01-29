/*
CreatorEngine
Class CrSingleton
Payne
*/

#ifndef _CREATOR_SINGLETON_H
#define _CREATOR_SINGLETON_H

template <class T>
class CrSingleton
{
public:
	static T * Instance();
protected:
	static T * m_pInstance;
protected:
	CrSingleton();
public:
	virtual ~CrSingleton() = 0;

};

template<class T>
T * CrSingleton<T>::m_pInstance = nullptr;

template<class T>
T * CrSingleton<T>::Instance()
{
	if (!m_pInstance)
	{
		static T instance;
		m_pInstance = &instance;
	}
	return m_pInstance;
}

template<class T>
CrSingleton<T>::CrSingleton()
{

}

template<class T>
CrSingleton<T>::~CrSingleton()
{

}

#endif