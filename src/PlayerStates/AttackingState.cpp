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

    default:
        break;
    }
}

void AttackingState::enter(Player& player)
{
    std::cout << "enter:: AttackingState\n";

    player.attack();


}

void AttackingState::update(Player& player, float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_attackDuration)
    {
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}
