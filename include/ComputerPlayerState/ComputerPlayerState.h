#pragma once

class ComputerPlayer;

class ComputerPlayerState {
public:
    virtual ~ComputerPlayerState() = default;

    virtual void enter(ComputerPlayer& player) = 0;
    virtual void update(ComputerPlayer& player, float deltaTime) = 0;
    virtual void exit(ComputerPlayer& player) = 0;
};
