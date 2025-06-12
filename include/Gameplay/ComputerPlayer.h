#pragma once
#include "Objects/PlayableObject.h"

class ComputerPlayer : public PlayableObject{
public:
	ComputerPlayer(const std::string& name) : PlayableObject(name) { }
};
