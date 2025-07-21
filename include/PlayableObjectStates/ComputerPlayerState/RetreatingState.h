#pragma once
#include <SFML/System/Vector2.hpp>
#include "Objects/Object.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class RetreatingState : public ComputerPlayerState {
public:
    RetreatingState(); 
    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    void name() {};

private:
    // time of retreating can also be determined according to hp level, ect.
    float m_retreatDuration = RETREAT_DURATION; // Duration of retreating
    float m_elapsedTime = 0.0f;
    sf::Vector2f m_safeZone;
};
