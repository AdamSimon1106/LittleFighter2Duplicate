//#pragma once
//
//#include "ComputerPlayerState/ComputerPlayerState.h"
//#include <memory>
//
//class PickableObject;
//
//class PickingUpItemState : public ComputerPlayerState {
//public:
//    explicit PickingUpItemState(std::shared_ptr<PickableObject> item);
//
//    void enter(ComputerPlayer& player) override;
//    void update(ComputerPlayer& player, float deltaTime) override;
//    void exit(ComputerPlayer& player) override;
//
//private:
//    std::shared_ptr<PickableObject> m_targetItem;
//};
