#pragma once
#include "SFML/Graphics.hpp"
#include "Objects/PlayableObject.h"

class Player : public PlayableObject{
public:
private:
	sf::Text m_name;
};
