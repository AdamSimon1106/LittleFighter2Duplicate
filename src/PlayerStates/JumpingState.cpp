#include "PlayableObjectStates/PlayerStates/JumpingState.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "PlayableObjectStates/PlayerStates/JumpBasePhase/RisingPhase.h"

#include "GamePlay/Player.h"

JumpingState::JumpingState(Input input)
{
    m_input = input;
}

std::unique_ptr<PlayableObjectState> JumpingState::handleInput(Input input)
{



    return nullptr;
}

void JumpingState::enter(PlayableObject& player)
{

    player.setAniName("jumping");

    m_groundY = player.getPosition().y;
    m_phase = std::make_unique<RisingPhase>(0.15f, 650.f, player.getPosition().y);
}

void JumpingState::update(PlayableObject& player, float dt)
{
    if (!m_phase) {
        player.adjustBoundsBack();
        player.setState(std::make_unique<StandingState>(Input::NONE));
        return;
    }

    if (auto next = m_phase->update(player, dt)) {
        m_phase = std::move(next);
    }
    else if (player.getPosition().y >= m_groundY) {
        player.adjustBoundsBack();
        player.setState(std::make_unique<StandingState>(Input::NONE));
    }

}



