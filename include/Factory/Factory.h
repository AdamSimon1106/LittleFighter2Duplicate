#pragma once
#include <memory>
#include "Objects/Object.h"
#include <string>
#include <map>
#include <functional>

 

template<typename T>
class Factory {
public:
	static std::unique_ptr<T> create(const std::string& name);
	using creatorFunc = std::function<std::unique_ptr<T>()>;
	static bool registerIt(const std::string& name, creatorFunc f);
private:

	typedef std::map<std::string, creatorFunc > myMap;

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
inline bool Factory<T>::registerIt(const std::string& name, creatorFunc f)
{
	getMap().emplace(name, f);
	return true;
}
