#include "PlayerStates/AttackingState.h"
#include"PlayerStates/StandingState.h"
#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> AttackingState::handleInput(Input input)
{
    return std::make_unique<StandingState>(input);
    return nullptr;
}

void AttackingState::enter(Player& player)
{
    std::cout << "enter:: AttackingState\n";

    const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

    Animation attackAnim(&tex,
        0, 240,       // ���� �������� �� ����� (��� sprite sheet ���)
        80, 80,       // ���� �����
        3,            // 3 ������� �� �����
        0.1f,         // ��� ���� �����
        false);       // �� ������ � ����� ���� ��� ���

    player.setAnimation(attackAnim);

    // ���������: ����� �����
    //player.setVelocity({ 0.f, 0.f });

    // ���������: ����� ����� ����� ������ (��� ������)
    // ���� ��� �� attack timer ���� ��state

}
