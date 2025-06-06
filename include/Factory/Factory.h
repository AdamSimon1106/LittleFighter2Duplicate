#pragma once
#include <memory>
#include "Objects/Object.h"
#include <string>
#include <map>

 

template<typename T>
class Factory {
public:
	static std::unique_ptr<T> create(const std::string& name);
	static bool registerit(const std::string& name, std::unique_ptr<T>(*f)());
private:

	typedef std::map<std::string, std::unique_ptr<T>(*)()> myMap;

	static myMap& getMap()
	{
		static myMap m_map;
		return m_map;
	}
};

template<typename T>
inline std::unique_ptr<T> Factory<T>::create(const std::string& name)
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}

template<typename T>
inline bool Factory<T>::registerit(const std::string& name, std::unique_ptr<T>(*f)())
{
	getMap().emplace(name, f);
	return true;
}
