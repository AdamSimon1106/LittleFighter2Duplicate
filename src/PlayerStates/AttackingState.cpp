#include "PlayerStates/AttackingState.h"
#include"PlayerStates/StandingState.h"
#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> AttackingState::handleInput(Input input)
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

void AttackingState::enter(Player& player)
{
    std::cout << "enter:: AttackingState\n";
    player.setAniName("attacking");
    player.attack();
}

void AttackingState::update(Player& player, float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_attackDuration)
    {
        player.setStrategyName("");
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}
