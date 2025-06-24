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

    Animation attackAnim(player.getTexture(),
        640, 0,       // ���� �������� �� ����� (��� sprite sheet ���)
        80, 80,       // ���� �����
        2,            // 3 ������� �� �����
        0.1f,         // ��� ���� �����
        true);       // �� ������ � ����� ���� ��� ���

    player.setAnimation(attackAnim);
}
