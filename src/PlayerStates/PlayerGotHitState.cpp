#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "Objects/PlayableObject.h"

std::unique_ptr<PlayableObjectState> PlayerGotHitState::handleInput(Input input)
{
	return nullptr;
}


void PlayerGotHitState::enter(PlayableObject& player)
{
	std::cout << "PlayerGotHitState::enter\n";

	player.setAniName("gothit");
	player.dropHeldObj();
	m_elapsedTime = 0.0f;
}

void PlayerGotHitState::update(PlayableObject& player, float dt)
{
	std::cout << "PlayerGotHitState::update\n";

	m_elapsedTime += dt;

	if (m_elapsedTime >= m_recoveryTime) {
		player.setState(std::make_unique<StandingState>(Input::NONE));
	}
}
