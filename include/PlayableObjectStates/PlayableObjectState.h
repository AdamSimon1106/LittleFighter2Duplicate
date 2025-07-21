#pragma once
#include <memory>

enum Input
{
    PRESS_LEFT,
    PRESS_RIGHT,
    RELEASE_LEFT,
    RELEASE_RIGHT,
    PRESS_UP,
    PRESS_DOWN,
    RELEASE_UP,
    RELEASE_DOWN,
    PRESS_JUMP,
    PRESS_FALLING,
    PRESS_ATTACK,
    END_ATTACK,
    ADD_OBJ,
    NONE,
};

class PlayableObject;

class PlayableObjectState {
public:
    virtual ~PlayableObjectState() = default;
    virtual void enter(PlayableObject& player) = 0;
    virtual void update(PlayableObject& player, float deltaTime) = 0;
    virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) = 0;


    // in-game events:
    virtual void onHandsAttack(PlayableObject& player) = 0;
    virtual void onStoneHit(PlayableObject& player) = 0;
    virtual void onExplosion(PlayableObject& player) = 0;
    virtual void onBoxHit(PlayableObject& player) = 0;
    virtual bool isAccessible() const { return true; }
    virtual void name() = 0; // for debug only... (u can add this func to verify that you are in the correct state)
};
