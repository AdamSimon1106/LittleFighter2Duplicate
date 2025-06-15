#pragma once
#include "PlayerStates/JumpBasePhase/JumpPhaseBase.h"
#include <SFML/System.hpp>

class HangingPhase : public JumpPhaseBase {
public:
    HangingPhase(float duration, float groundY);
    std::unique_ptr<JumpPhaseBase> update(Player& player, float dt) override;

private:
    sf::Clock m_clock;
    float m_duration;
    float m_groundY;
};