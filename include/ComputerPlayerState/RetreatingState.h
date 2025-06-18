#pragma once

#include "ComputerPlayerState/ComputerPlayerState.h"

class RetreatingState : public ComputerPlayerState {
public:
    RetreatingState(); 
    void enter(ComputerPlayer& player) override;
    void update(ComputerPlayer& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

private:
    // time of retreating can also be determined according to hp level, ect.
    float m_retreatDuration = 2.0f; // Duration of retreating
    float m_elapsedTime = 0.0f;
};
