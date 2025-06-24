#pragma once
#include "PlayerStates/JumpBasePhase/JumpPhaseBase.h"
#include <SFML/System.hpp>

class FallingPhase : public JumpPhaseBase {
public:
    FallingPhase(float speed, float groundY);
    std::unique_ptr<JumpPhaseBase> update(Player& player, float dt) override;

private:
    float m_speed;
    float m_groundY;
};
