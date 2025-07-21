#pragma once
#include "Objects/Object.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include "Consts/Consts.h"
#include <memory>

class PlayableObject;

class AttackingState : public ComputerPlayerState {
public:
    explicit AttackingState(std::shared_ptr<Object> target);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void name();
private:
    std::shared_ptr<Object> m_target; // the target for attacking
    float m_attackCooldown = ATTACK_COOLDOWN; // time betweeen attacks
    void alignAttacker(PlayableObject& player);
};
