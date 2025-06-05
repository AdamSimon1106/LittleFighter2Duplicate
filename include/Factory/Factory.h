#pragma once
#include <memory>
#include "Objects/Object.h"
#include <string>
#include <map>

 

template<typename T>
class Factory {
public:
	static std::unique_ptr<T> create(const std::string& name);
	static bool registerit(const std::string& name, std::unique_ptr<T>(*)());
private:
	static mymap& getMap()
	{
		static std::map<std::string, std::unique_ptr<T>(*)()> m_map;
		return m_map;
	}
};

template<typename T>
static std::unique_ptr<T> create(const std::string& name) {

	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}

template<typename T>
static bool registerit(const std::string& name, std::unique_ptr<T>(*)()) {
	getMap().emplace(name, f);
	return true;
}



