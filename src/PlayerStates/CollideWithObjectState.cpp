
#include "PlayableObjectStates/PlayerStates/CollideWithObjectState.h"
#include "PlayableObjectStates/PlayerStates/JumpingState.h"
#include "PlayableObjectStates/PlayerStates/WalkingState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/PlayerStates/KnockedState.h"
#include "PlayableObjectStates/PlayerStates/PlayerGotHitState.h"

#include "Gameplay/Player.h"

class PlayableObject;

CollideWithObject::CollideWithObject(Input input, std::shared_ptr<PickableObject> obj)
	:m_obj(obj)
{
	m_input = input;
}

std::unique_ptr<PlayableObjectState> CollideWithObject::handleInput(Input input)
{
	if (input == Input::ADD_OBJ)
	{
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
	case Input::PRESS_ATTACK:
		return std::make_unique<AttackState>();

	}

	return nullptr;
}

void CollideWithObject::enter(PlayableObject& player)
{
	std::cout << "CollideWithObject::enter\n";
}

void CollideWithObject::update(PlayableObject& player, float dt)
{
	if (m_pickupPending && m_obj->onEarth())
	{
		player.pickUpObject(m_obj);
		m_obj->pick();
		m_pickupPending = false;
		player.setState(std::make_unique<StandingState>(Input::NONE));
	}
}

void CollideWithObject::onHandsAttack(PlayableObject& player)
{
	player.setState(std::make_unique<PlayerGotHitState>());
}

void CollideWithObject::onStoneHit(PlayableObject& player)
{
	player.setState(std::make_unique<KnockedState>());
}

void CollideWithObject::onBoxHit(PlayableObject& player)
{
	player.setState(std::make_unique<KnockedState>());
}

void CollideWithObject::onExplosion(PlayableObject& player)
{
	player.setState(std::make_unique<KnockedState>());
}
