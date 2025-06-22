//#pragma once
//
//#include "ComputerPlayerState/ComputerPlayerState.h"
//#include <memory>
//
//class PlayableObject;
//
//class ApproachingEnemyState : public ComputerPlayerState {
//public:
//    explicit ApproachingEnemyState(std::shared_ptr<PlayableObject> target);
//
//    void enter(ComputerPlayer& player) override;
//    void update(ComputerPlayer& player, float deltaTime) override;
//    void exit(ComputerPlayer& player) override;
//
//private:
//    std::shared_ptr<PlayableObject> m_target; // the enemy we approaching
//};
