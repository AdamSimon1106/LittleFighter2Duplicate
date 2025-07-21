#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "PlayableObjectStates/PlayerStates/WalkingState.h" 
#include "PlayableObjectStates/PlayerStates/JumpingState.h"
#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/PlayerStates/KnockedState.h"
#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"

#include "Gameplay/Player.h"
#include <iostream>
StandingState::StandingState(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayableObjectState> StandingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::PRESS_UP:
	case Input::PRESS_DOWN:
	case Input::PRESS_LEFT:
	case Input::PRESS_RIGHT:
		return std::make_unique<WalkingState>(input);
	case Input::PRESS_JUMP:
		return std::make_unique<JumpingState>(input);
	case Input::PRESS_ATTACK:
		return std::make_unique<AttackState>();

	default:
		break;
	}
	return nullptr;
}

void StandingState::enter(PlayableObject& player)
{
	player.setAniName("standing");
	
	player.resetDirection();
}

void StandingState::onHandsAttack(PlayableObject& player)
{
	player.setState(std::make_unique<PlayerGotHitState>());
}

void StandingState::onStoneHit(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}

void StandingState::onBoxHit(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}

void StandingState::onExplosion(PlayableObject& player)
{
	player.setAniName("knockedDown");
	player.setState(std::make_unique<KnockedState>());
}
