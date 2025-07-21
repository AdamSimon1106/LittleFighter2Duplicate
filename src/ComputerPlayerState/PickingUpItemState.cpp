#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PickableObject.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>

PickingUpItemState::PickingUpItemState(std::shared_ptr<Object> item)
    : m_target(std::move(item)) {}

void PickingUpItemState::enter(PlayableObject& player) {
    
    player.setAniName("walking");
}

void PickingUpItemState::update(PlayableObject& player, float deltaTime) {
    


    m_targetItem = std::dynamic_pointer_cast<PickableObject>(m_target);
   
    if (!m_targetItem ||!m_targetItem->onEarth()) {
        // Item already gone – return to idle
        m_targetItem = nullptr;
        player.wantItem();
        
        player.setState(std::make_unique<IdleState>());
        return;
    }

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f itemPos = m_targetItem->getPosition();

    float distance = std::sqrt(std::pow(playerPos.x - itemPos.x, 2) +
        std::pow(playerPos.y - itemPos.y, 2));


    if (distance <= PICK_UP_RANGE) {
        // Pick up item
        player.pickUpObject(m_targetItem);
        player.tookItem();
        player.setState(std::make_unique<IdleState>());
    }
    else {
        // Move toward item
        sf::Vector2f direction = itemPos - playerPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0.f)
            direction /= length;

        player.move(direction * player.getSpeed() * deltaTime);
    }
}

void PickingUpItemState::exit(ComputerPlayer& player) {

}

void PickingUpItemState::name() {
}

void PickingUpItemState::onHandsAttack(PlayableObject& player) {
    player.setState(std::make_unique<BlockingState>());

}

void PickingUpItemState::onStoneHit(PlayableObject& player) {
    player.setState(std::make_unique<GotHitState>());
}
void PickingUpItemState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedDownState>());
}
void PickingUpItemState::onExplosion(PlayableObject& player) {

}
