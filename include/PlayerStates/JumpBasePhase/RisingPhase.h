#pragma once

#include "PlayerStates/JumpBasePhase/JumpPhaseBase.h"
#include <SFML/System.hpp>

class RisingPhase : public JumpPhaseBase {
public:
    RisingPhase(float duration, float speed , float groundY);
    std::unique_ptr<JumpPhaseBase> update(Player& player, float dt) override;

private:
    sf::Clock m_clock;
    float m_duration;
    float m_speed;
    float m_groundY;
};