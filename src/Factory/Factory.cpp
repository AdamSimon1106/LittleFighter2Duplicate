#include "Factory/Factory.h"

std::unique_ptr<Object> Factory::create(const std::string& name) {
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}

bool Factory::registerit(const std::string& name, std::unique_ptr<Object>(*f)()) {
	getMap().emplace(name, f);
	return true;
}