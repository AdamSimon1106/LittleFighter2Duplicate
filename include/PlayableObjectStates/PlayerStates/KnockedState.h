#pragma once
#include "Consts/Consts.h"
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"

class KnockedState : public PlayerBaseState {
public:
    KnockedState() = default;;
    virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
    virtual void enter(PlayableObject& player) override;
    virtual void update(PlayableObject& player, float dt) override;

	bool isAccessible() const override { return false; }
    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;

private:
    float m_recoveryTime = KNOCKED_RECOVERY_TIME;  // Time lying down before recovery
    float m_elapsedTime = 0.0f;
};