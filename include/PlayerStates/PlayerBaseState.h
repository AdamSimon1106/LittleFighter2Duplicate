#pragma once
#include <memory>
#include <iostream>
#include "SFML/Graphics.hpp"
#include"Management/ResourceManager.h"
#include "Management/Animation.h"

class Player;

enum Input
{
	PRESS_LEFT,
	PRESS_RIGHT,
	RELEASE_LEFT,
	RELEASE_RIGHT,
	PRESS_JUMP
};


class Player;

class PlayerBaseState {
public:
	virtual ~PlayerBaseState() = default;
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) = 0;
	virtual void enter(Player& player) = 0;
	virtual void update(Player& player, float dt) { };
	

protected:
	Input m_input;
};
