#include "PlayerStates/JumpingState.h"
#include"PlayerStates/StandingState.h"

#include "GamePlay/Player.h"
#include <iostream>

std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
{
	
	return std::make_unique<StandingState>();
}

void JumpingState::enter(Player& player)
{
	std::cout << "enter:: JumpingState\n";

	// ���� ����� �� ������� ���������� �� ����� ��� ������
	// player.setVerticalSpeed(-jumpSpeed); // �� �� �� ������� ���
}
