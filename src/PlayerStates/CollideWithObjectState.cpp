#include "PlayerStates/CollideWithObjectState.h"
#include "PlayerStates/StandingState.h"

CollideWithObject::CollideWithObject(Input input)
{
	m_input = input;
}

std::unique_ptr<PlayerBaseState> CollideWithObject::handleInput(Input input)
{
	switch (input)
	{
	case ADD_OBJ:
		std::cout << "pic obj\n";
		//set strategy;
		return  std::make_unique<StandingState>(input);
		
		break;
	case PRESS_LEFT:
		break;
	case PRESS_RIGHT:
		break;
	case RELEASE_LEFT:
		break;
	case RELEASE_RIGHT:
		break;
	case PRESS_UP:
		break;
	case PRESS_DOWN:
		break;
	case RELEASE_UP:
		break;
	case RELEASE_DOWN:
		break;
	case PRESS_JUMP:
		break;
	case PRESS_ATTACK:
		break;
	case END_ATTACK:
		break;
	case NONE:
		break;
	default:
		break;
	}

	return nullptr;
}

void CollideWithObject::enter(Player& player)
{
}
