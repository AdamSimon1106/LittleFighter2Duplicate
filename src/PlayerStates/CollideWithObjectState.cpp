
#include "PlayerStates/CollideWithObjectState.h"
#include "PlayerStates/JumpingState.h"
#include "PlayerStates/WalkingState.h"
#include "PlayerStates/StandingState.h"
#include "PlayerStates/AttackState.h"
#include "Gameplay/Player.h"


CollideWithObject::CollideWithObject(Input input, PickableObject* obj)
	:m_obj(obj)
{
	m_input = input;
}

std::unique_ptr<PlayerBaseState> CollideWithObject::handleInput(Input input)
{
	if (input == Input::ADD_OBJ)
	{
		std::cout << "Handling ADD_OBJ\n";
		m_pickupPending = true;
		return nullptr;
	}
	switch (input)
	{
	case Input::PRESS_UP:
	case Input::PRESS_DOWN:
	case Input::PRESS_LEFT:
	case Input::PRESS_RIGHT:
		return std::make_unique<WalkingState>(input);
	case Input::RELEASE_LEFT:
	case Input::RELEASE_RIGHT:
	case Input::RELEASE_DOWN:
	case Input::RELEASE_UP:
		return std::make_unique<StandingState>(input);
	case Input::PRESS_JUMP:
		return std::make_unique<JumpingState>(input);

	}

	return nullptr;
}

void CollideWithObject::enter(Player& player)
{
	std::cout << "enter::CollideWithObject\n";

	//player.setDiraction(m_input);
}

void CollideWithObject::update(Player& player, float dt)
{
	if (m_pickupPending)
	{
		player.pickUpObject(m_obj);
		m_pickupPending = false;
		player.setState(std::make_unique<StandingState>(Input::NONE));
	}
}
