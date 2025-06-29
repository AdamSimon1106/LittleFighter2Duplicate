#include "PlayerStates/AttackState.h"
#include"PlayerStates/StandingState.h"
#include "GamePlay/Player.h"
#include <iostream>


std::unique_ptr<PlayerBaseState> AttackState::handleInput(Input input)
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

void AttackState::enter(Player& player)
{
    std::cout << "enter:: AttackingState Player\n";
    
    player.setAniName("attacking");
    std::cout << "after setAniName\n";
    player.attack();
    std::cout << "after attack()\n";
}

void AttackState::update(Player& player, float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_attackDuration)
    {
        player.setStrategyName("");
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}
