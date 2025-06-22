//#include "PlayerStates/StandingState.h"
//#include "PlayerStates/WalkingState.h" 
//#include "PlayerStates/JumpingState.h"
//#include "PlayerStates/AttackingState.h"
//#include"Gameplay/Player.h"
//
//StandingState::StandingState(Input input)
//{
//	m_input = input;
//}
//
//std::unique_ptr<PlayerBaseState> StandingState::handleInput(Input input)
//{
//	switch (input)
//	{
//	case Input::PRESS_UP:
//	case Input ::PRESS_DOWN:
//	case Input::PRESS_LEFT:
//	case Input::PRESS_RIGHT:
//		 return std::make_unique<WalkingState>(input);
//	case Input::PRESS_JUMP:
//		return std::make_unique<JumpingState>(input);
//	case Input::PRESS_ATTACK:
//		return std::make_unique<AttackingState>();
//
//	default:
//		break;
//	}
//	return nullptr;
//}
//
//void StandingState::enter(Player& player)
//{
//	std::cout << "enter:: StandingState\n";
//	
//	Animation standingAnim(player.getTexture(),
//		0, 0,          // x, y
//		80, 80,        // width, height
//		3,             // מספר פריימים
//		0.2f);         // זמן בין פריימים
//
//	player.setAnimation(standingAnim);
//	player.setDiraction(m_input);
//	
//}
