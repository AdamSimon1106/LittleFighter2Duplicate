#pragma once
#include <memory>
#include "Objects/Object.h"
#include <string>
#include <map>

typedef std::map<std::string, std::unique_ptr<Object>(*)()> mymap;
class Factory {
public:
	static std::unique_ptr<Object> create(const std::string& name);
	static bool registerit(const std::string& name, std::unique_ptr<Object>(*)());
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};