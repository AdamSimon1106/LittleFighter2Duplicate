#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"

#include"Gameplay/Player.h"


std::unique_ptr<PlayerBaseState> WalkingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::RELEASE_LEFT:
		return std::make_unique<StandingState>();
	case Input::RELEASE_RIGHT:
		std::cout << "in WalkingState release right\n";
		return std::make_unique<StandingState>();

	default:
		break;
	}
	return nullptr;
}

void WalkingState::enter(Player& player)
{
	std::cout << "enter:: WalkingState\n";

	const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

	Animation walkingAnim(&tex,
		0, 80,       // x, y
		80, 80,      // width, height
		4,           // frame count
		0.15f);      // frame time


	player.setAnimation(walkingAnim);
	player.setDiraction(m_input);
	player.move();
}
