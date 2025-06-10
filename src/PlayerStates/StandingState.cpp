#include "PlayerStates/StandingState.h"
#include "PlayerStates/WalkingState.h" 


std::unique_ptr<PlayerBaseState> StandingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::PRESS_LEFT:
		m_input = input;
	case Input::PRESS_RIGHT:
		m_input = input;
		 return std::make_unique<WalkingState>();

	default:
		break;
	}
	return nullptr;
}

void StandingState::enter(Player& player)
{
	std::cout << "enter:: StandingState\n";
}
