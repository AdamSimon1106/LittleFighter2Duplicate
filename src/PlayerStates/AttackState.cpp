#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "EventCommands/HandsAttackCommand.h"
#include "PlayableObjectStates/PlayerStates/KnockedState.h"
#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"

#include "GamePlay/Player.h"
#include <iostream>


std::unique_ptr<PlayableObjectState> AttackState::handleInput(Input input)
{
    switch (input)
    {

    case END_ATTACK:
        return std::make_unique<StandingState>(input);
        break;
	case PRESS_ATTACK:
		return nullptr;
		break;

    default:
        break;
    }
	return nullptr; 
}

void AttackState::enter(PlayableObject& player)
{
    std::cout << "AttackState::enter\n";

    player.setAniName("attacking");
    player.attack();
}

void AttackState::update(PlayableObject& player, float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_attackDuration)
    {
        player.setStrategyName("");
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}

void AttackState::onHandsAttack(PlayableObject& player)
{
    player.setState(std::make_unique<PlayerGotHitState>());
}

void AttackState::onStoneHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedState>());
}

void AttackState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedState>());
}

void AttackState::onExplosion(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedState>());
}
