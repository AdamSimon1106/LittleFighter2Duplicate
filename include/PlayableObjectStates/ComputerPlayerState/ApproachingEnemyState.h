#pragma once
#include "Objects/Object.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include <memory>

class PlayableObject;

class ApproachingEnemyState : public ComputerPlayerState {
public:
    explicit ApproachingEnemyState(std::shared_ptr<Object> target);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    void name();
private:
    std::shared_ptr<Object> m_target; // the enemy we approaching
};
