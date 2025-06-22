#pragma once
#include "Objects/PickableObject.h"

class Weapon : public PickableObject{
public:
	Weapon(const sf::Vector2f pos, const std::string& name);
private:
};
