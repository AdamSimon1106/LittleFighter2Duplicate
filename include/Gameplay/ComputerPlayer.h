#pragma once
#include "Objects/PlayableObject.h"

class ComputerPlayer : public PlayableObject{
public:
	ComputerPlayer(sf::Texture tex) : PlayableObject(tex) { }
};
