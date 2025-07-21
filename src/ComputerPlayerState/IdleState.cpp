#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "GamePlay/ComputerPlayer.h"  
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h" // the next state
#include <cmath> // distance calculation
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"


void IdleState::enter(PlayableObject& player) {

    player.setAniName("standing");
}

void IdleState::update(PlayableObject& player, float deltaTime) {
    
    std::shared_ptr<Object> target = player.getTarget();
    if (!target)
    {
        return;
    }
    if (std::dynamic_pointer_cast<PlayableObject>(target)) {
        player.setState(std::make_unique<ApproachingEnemyState>(target));
        return;
    }
    else if (std::dynamic_pointer_cast<PickableObject>(target)) {
        player.setState(std::make_unique<PickingUpItemState>(target));
        return;
    }
    
}

void IdleState::exit(ComputerPlayer& player) {
    // Optional: stop idle animation, log transition, etc.
}

void IdleState::onHandsAttack(PlayableObject& player) {
    player.setState(std::make_unique<BlockingState>());

}

void IdleState::onStoneHit(PlayableObject& player) {

}
void IdleState::onBoxHit(PlayableObject& player)
{
}
void IdleState::onExplosion(PlayableObject& player) {
    player.setState(std::make_unique<GotHitState>());

}

void IdleState::name() {
}