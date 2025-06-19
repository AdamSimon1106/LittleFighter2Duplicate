//#pragma once
//
//#include "ComputerPlayerState/ComputerPlayerState.h"
//#include <memory>
//
//class PlayableObject;
//
//class AttackingState : public ComputerPlayerState {
//public:
//    explicit AttackingState(PlayableObject* target);
//
//    void enter(ComputerPlayer& player) override;
//    void update(ComputerPlayer& player, float deltaTime) override;
//    void exit(ComputerPlayer& player) override;
//
//private:
//    PlayableObject* m_target; // the target for attacking
//    float m_attackCooldown = 0.f; // time betweeen attacks
//};
