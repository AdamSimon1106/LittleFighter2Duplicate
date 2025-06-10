#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"

#include"Gameplay/Player.h"


std::unique_ptr<PlayerBaseState> WalkingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::RELEASE_LEFT:
	case Input::RELEASE_RIGHT:
		return std::make_unique<StandingState>();

	default:
		break;
	}
	return nullptr;
}

void WalkingState::enter(Player& player)
{
	std::cout << "in walkingState:: enter\n";
	std::cout << "enter:: WalkingState\n";

	const sf::Texture& tex = ResourceManager::instance().getTexture("hunter");

	Animation walkingAnim(&tex,
		sf::IntRect(0, 80, 80, 80),  // לדוגמה: שורת ההליכה מתחילה ב־y = 80
		sf::IntRect(240, 80, 80, 80), // 4 פריימים: 0, 80, 160, 240
		0.15f); // זמן פריים מהיר יותר מ־standing

	player.setAnimation(walkingAnim);
}
