#include "PlayerStates/JumpingState.h"
#include"PlayerStates/StandingState.h"

#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
{
	
	return std::make_unique<StandingState>();
    return nullptr;
}

void JumpingState::enter(Player& player)
{
	std::cout << "enter:: JumpingState\n";

	// ���� ����� �� ������� ���������� �� ����� ��� ������
	// player.setVerticalSpeed(-jumpSpeed); // �� �� �� ������� ���

    std::cout << "enter:: JumpingState\n";

    const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

    Animation jumpingAnim(&tex,
        0, 160,       // x, y � ���� ��� ���� ������
        80, 80,       // width, height
        2,            // 2 ������� ������ ������
        0.25f);       // ��� ���� ����

    player.setAnimation(jumpingAnim);
}

