#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"

#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath> 
#include <iostream>

ApproachingEnemyState::ApproachingEnemyState(std::shared_ptr<Object> target)
    : m_target(std::move(target)) {
}

void ApproachingEnemyState::enter(PlayableObject& player) {
    
    player.setAniName("walking");

}
void ApproachingEnemyState::update(PlayableObject& player, float deltaTime) {
    if (!m_target)
        return;

    if (!player.getTarget()) {
        player.setState(std::make_unique<IdleState>());
        return;
    }

    if (auto object = std::dynamic_pointer_cast<PickableObject>(m_target)) {
        player.setState(std::make_unique<PickingUpItemState>(object));
        return;
    }

    if (auto enemy = std::dynamic_pointer_cast<PlayableObject>(m_target)) {
        if (!enemy->getState()->isAccessible()) {
            m_target = player.getTarget();
        }
    }

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f targetPos = m_target->getPosition();
    float dx = targetPos.x - playerPos.x;
    float dy = targetPos.y - playerPos.y;

    float absDy = std::abs(dy);
    float attackRange = player.getAttackRange();

    // אם בתוך טווח התקיפה, עבור לתקיפה
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance < attackRange && absDy < 20.f) {
        player.setState(std::make_unique<AttackingState>(m_target));
        return;
    }

    sf::Vector2f direction(0.f, 0.f);
    if (absDy > 20.f) {
        direction.y = (dy > 0) ? 1.f : -1.f; // up/down only
    }
    else {
        direction.x = (dx > 0) ? 1.f : -1.f; // left/right only
        // keep y in the same level
        if (absDy > 5.f)
            direction.y = (dy > 0) ? 0.2f : -0.2f; 
    }

    float speed = player.getSpeed();
    player.move(direction * speed * deltaTime);

    if (player.getHeldObj()) {
        player.getHeldObj()->move(player.getPosition());
    }
}


void ApproachingEnemyState::exit(ComputerPlayer& player) {
}

void ApproachingEnemyState::onHandsAttack(PlayableObject& player) {

    player.setState(std::make_unique<BlockingState>());

}

void ApproachingEnemyState::onStoneHit(PlayableObject& player) {
    player.setState(std::make_unique<GotHitState>());
}
void ApproachingEnemyState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedDownState>());
}
void ApproachingEnemyState::onExplosion(PlayableObject& player) {

}
void ApproachingEnemyState::name() {
}
