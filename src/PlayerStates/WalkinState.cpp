#include "PlayableObjectStates/PlayerStates/WalkingState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/PlayerStates/KnockedState.h"
#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"

#include "Gameplay/Player.h"


WalkingState::WalkingState(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayableObjectState> WalkingState::handleInput(Input input)
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

void WalkingState::enter(PlayableObject& player)
{
	player.setAniName("walking");
	player.setDiraction(m_input);
	
}

void WalkingState::onHandsAttack(PlayableObject& player)
{
	
	player.setState(std::make_unique<PlayerGotHitState>());
	
}

void WalkingState::onBoxHit(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}

void WalkingState::onStoneHit(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}

void WalkingState::onExplosion(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}
