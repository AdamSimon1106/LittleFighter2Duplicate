#pragma once
#include "Objects/Object.h"


class PickableObject : public Object {
public:
	PickableObject(const sf::Vector2f pos, const std::string& name);
	const std::string& getName();
	virtual void move(sf::Vector2f goal);
	virtual void playAttack() = 0;
protected:
	sf::Vector2f m_offset;
private:
	sf::Vector2f m_goalPosition;

	std::string m_name;
};
