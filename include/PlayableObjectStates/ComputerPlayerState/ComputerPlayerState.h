#pragma once
#include "PlayableObjectStates/PlayableObjectState.h"

class ComputerPlayer;

class ComputerPlayerState : public PlayableObjectState {
public:
    virtual ~ComputerPlayerState() = default;
    std::unique_ptr<PlayableObjectState> handleInput(Input input) { return nullptr; };

    virtual void exit(ComputerPlayer& player) = 0;
    virtual void onBoxHit(PlayableObject& player) override {};
};
