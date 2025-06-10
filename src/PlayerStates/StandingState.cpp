#include "PlayerStates/StandingState.h"
#include "PlayerStates/WalkingState.h" 
#include "PlayerStates/JumpingState.h"
#include "PlayerStates/AttackingState.h"
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
	case Input::PRESS_JUMP:
		return std::make_unique<JumpingState>();
	case Input::PRESS_ATTACK:
		return std::make_unique<AttackingState>();

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
		0, 0,          // x, y
		80, 80,        // width, height
		3,             // מספר פריימים
		0.2f);         // זמן בין פריימים

	player.setAnimation(standingAnim);
	
}
