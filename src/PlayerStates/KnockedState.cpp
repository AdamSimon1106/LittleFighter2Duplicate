#include "PlayableObjectStates/PlayerStates/KnockedState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "Objects/PlayableObject.h"


std::unique_ptr<PlayableObjectState> KnockedState::handleInput(Input input)
{
    return nullptr;
}

void KnockedState::enter(PlayableObject& player)
{
    player.setAniName("knockedDown");
    player.dropHeldObj();
    m_elapsedTime = 0.5f;
    player.resetDirection();
}

void KnockedState::onHandsAttack(PlayableObject& player)
{
}

void KnockedState::onStoneHit(PlayableObject& player)
{
}

void KnockedState::onBoxHit(PlayableObject& player)
{
}

void KnockedState::onExplosion(PlayableObject& player)
{
}

void KnockedState::update(PlayableObject& player, float dt)
{
    m_elapsedTime += dt;

    if (m_elapsedTime >= m_recoveryTime) {
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }
}
