#pragma once
#include <memory>
#include <iostream>

enum Input
{
	PRESS_LEFT,
	PRESS_RIGHT,
	RELEASE_LEFT,
	RELEASE_RIGHT
};


class Player;

class PlayerBaseState {
public:
	virtual ~PlayerBaseState() = default;
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) = 0;
	virtual void enter(Player& player) = 0;
protected:
	Input m_input;
};
