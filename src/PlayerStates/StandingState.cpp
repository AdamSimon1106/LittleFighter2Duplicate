#include "PlayerStates/StandingState.h"
#include "PlayerStates/WalkingState.h" 
#include"Gameplay/Player.h"

std::unique_ptr<PlayerBaseState> StandingState::handleInput(Input input)
{
	switch (input)
	{
	case Input::PRESS_LEFT:
		m_input = input;
		return std::make_unique<WalkingState>();
	case Input::PRESS_RIGHT:
		m_input = input;
		 return std::make_unique<WalkingState>();

	default:
		break;
	}
	return nullptr;
}

void StandingState::enter(Player& player)
{
	std::cout << "enter:: StandingState\n";
	const sf::Texture& tex = ResourceManager::instance().getTexture("hunter"); // או כל טקסטורה מתאימה

	Animation standingAnim(&tex,
		sf::IntRect(0, 0, 80, 80),  // התחלה: (x, y, width, height)
		sf::IntRect(180, 0, 80, 80), // סיום: x = 180 -> שלושה פריימים: 0, 60, 120, 180
		0.2f); // זמן פריים

	player.setAnimation(standingAnim);
	
}
