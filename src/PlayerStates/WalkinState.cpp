#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"

#include"Gameplay/Player.h"


WalkingState::WalkingState(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayerBaseState> WalkingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::RELEASE_LEFT:
	case Input::RELEASE_RIGHT:
	case Input::RELEASE_DOWN:
	case Input::RELEASE_UP:
		return std::make_unique<StandingState>(input);
	case Input::PRESS_LEFT:
	case Input::PRESS_RIGHT:
	case Input::PRESS_DOWN:
	case Input::PRESS_UP:
		return std::make_unique<WalkingState>(input);

	default:
		break;
	}
	return nullptr;
}

void WalkingState::enter(Player& player)
{
	std::cout << "enter:: WalkingState\n";
	player.setAniName("walking");
	player.setDiraction(m_input);
	
	
}