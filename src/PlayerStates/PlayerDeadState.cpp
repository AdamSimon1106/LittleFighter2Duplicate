#include "PlayableObjectStates/PlayerStates/PlayerDeadState.h"
#include "Objects/PlayableObject.h"

std::unique_ptr<PlayableObjectState> PlayerDeadState::handleInput(Input input)
{
	return nullptr;
}

void PlayerDeadState::enter(PlayableObject& player)
{
	player.setAniName("dead");
	player.resetDirection();
}
