#pragma once

#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"

class DeadState : public ComputerPlayerState {
public:
    void enter(PlayableObject& player) override; 
    void update(PlayableObject& player, float deltaTime) override { };
    void exit(ComputerPlayer& player) override {};

    void onHandsAttack(PlayableObject& player) override {};
    void onStoneHit(PlayableObject& player) override {};
    void onBoxHit(PlayableObject& player) override {};
    void onExplosion(PlayableObject& player) override {};
    bool isAccessible() const override { return false; }
    void name() {};
private:

};
