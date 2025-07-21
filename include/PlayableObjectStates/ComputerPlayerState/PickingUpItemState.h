#pragma once
#include "Objects/Object.h"
#include "PlayableObjectStates/ComputerPlayerState/ComputerPlayerState.h"
#include <memory>

class PickableObject;

class PickingUpItemState : public ComputerPlayerState {
public:
    explicit PickingUpItemState(std::shared_ptr<Object> item);

    void enter(PlayableObject& player) override;
    void update(PlayableObject& player, float deltaTime) override;
    void exit(ComputerPlayer& player) override;

    void onHandsAttack(PlayableObject& player) override;
    void onStoneHit(PlayableObject& player) override;
    void onBoxHit(PlayableObject& player) override;
    void onExplosion(PlayableObject& player) override;
    void name();

private:
    std::shared_ptr<Object> m_target;
    std::shared_ptr<PickableObject> m_targetItem;

};
