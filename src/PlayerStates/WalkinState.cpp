#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"



std::unique_ptr<PlayerBaseState> WalkingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::RELEASE_LEFT:
	case Input::RELEASE_RIGHT:
		return std::make_unique<StandingState>();

	default:
		break;
	}
	return nullptr;
}

void WalkingState::enter(Player& player)
{

}
