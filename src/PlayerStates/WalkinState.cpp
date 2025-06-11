#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"

#include"Gameplay/Player.h"


WalkingState::WalkingState(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayerBaseState> WalkingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::RELEASE_LEFT:
	case Input::RELEASE_RIGHT:
		return std::make_unique<StandingState>(input);

	default:
		break;
	}
	return nullptr;
}

void WalkingState::enter(Player& player)
{
	std::cout << "enter:: WalkingState\n";

	const sf::Texture& tex = ResourceManager::instance().getTexture("davis_ani");

	Animation walkingAnim(&tex,
		320, 0,       // x, y
		80, 80,      // width, height
		4,           // frame count
		0.2f);      // frame time


	player.setAnimation(walkingAnim);
	player.setDiraction(m_input);
	
	
}
