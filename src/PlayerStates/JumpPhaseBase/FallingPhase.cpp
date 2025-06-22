#include "PlayerStates/JumpBasePhase/FallingPhase.h"
#include "PlayerStates/StandingState.h"
#include "GamePlay/Player.h"

FallingPhase::FallingPhase(float speed, float groundY)
    : m_speed(speed), m_groundY(groundY) {}

std::unique_ptr<JumpPhaseBase> FallingPhase::update(Player& player, float dt) {
    auto pos = player.getPosition();
    pos.y += m_speed * dt;
    if (pos.y >= m_groundY) {
        pos.y = m_groundY;
        player.setPosition(pos);
        return nullptr;
    }

    player.setPosition(pos);
    player.setDiraction(PRESS_FALLING);
    return nullptr;
}
