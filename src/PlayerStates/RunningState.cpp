#include "PlayableObjectStates/PlayerStates/RunningState.h"

RunningState::RunningState(Input input)
{
}

std::unique_ptr<PlayableObjectState> RunningState::handleInput(Input input)
{
	return std::unique_ptr<PlayableObjectState>();
}

void RunningState::enter(PlayableObject& player)
{

	std::cout << "RunningState::enter" << std::endl;
}
