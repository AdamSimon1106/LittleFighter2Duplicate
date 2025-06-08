#pragma once
#include "Objects/PlayableObject.h"

class ComputerPlayer : public PlayableObject{
public:
	ComputerPlayer(const sf::Texture& tex) : PlayableObject(tex) { }
};
