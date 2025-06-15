// HangingPhase.cpp
#include "PlayerStates/JumpBasePhase/HangingPhase.h"
#include "PlayerStates/JumpBasePhase/FallingPhase.h"
#include "GamePlay/Player.h"

HangingPhase::HangingPhase(float duration, float groundY)
    : m_duration(duration), m_groundY(groundY) {
    m_clock.restart();
}

std::unique_ptr<JumpPhaseBase> HangingPhase::update(Player& player, float dt) {
    (void)dt;
    if (m_clock.getElapsedTime().asSeconds() >= m_duration)
    {
        std::cout << "HangingPhase, finished\n";
        return std::make_unique<FallingPhase>(700.f, m_groundY);
    }

    return nullptr;
}
