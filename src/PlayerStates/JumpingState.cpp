#include "PlayerStates/JumpingState.h"
#include"PlayerStates/StandingState.h"

#include "GamePlay/Player.h"

std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
{
    if (m_clock.getElapsedTime().asSeconds() >= m_duration)
    {
        return std::make_unique<StandingState>();
    }

    return nullptr;
}

void JumpingState::enter(Player& player)
{
	std::cout << "enter:: JumpingState\n";
    
    Animation jumpingAnim(player.getTexture(),
        0, 160,       // x, y � ���� ��� ���� ������
        80, 80,       // width, height
        2,            // 2 ������� ������ ������
        0.25f);       // ��� ���� ����

    player.setAnimation(jumpingAnim);
    player.setDiraction(m_input);

    m_clock.restart();
}

