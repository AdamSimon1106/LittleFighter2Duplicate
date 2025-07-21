#pragma once
#include "Consts/Consts.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class BlockingState : public ComputerPlayerState {
public:
    BlockingState();

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    void name();
private:
    float m_blockDuration = BLOCK_DURATION; // Time to stay in block
    float m_elapsedTime = 0.0f;
};
