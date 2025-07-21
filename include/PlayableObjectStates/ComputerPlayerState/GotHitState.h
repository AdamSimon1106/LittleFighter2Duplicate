#pragma once
#include "Consts/Consts.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class GotHitState : public ComputerPlayerState {
public:
    GotHitState();

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;

    void name() {};
private:
    float m_recoveryTime = HIT_RECOVERY_TIME;  // Time lying down before recovery
    float m_elapsedTime = 0.0f;
};
