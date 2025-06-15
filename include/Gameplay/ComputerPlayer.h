#pragma once
#include "Objects/PlayableObject.h"

class ComputerPlayer : public PlayableObject{
public:
	ComputerPlayer(const sf::Vector2f pos, const std::string& name) : PlayableObject(pos, name) { }
};
