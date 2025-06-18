#include "ComputerPlayerState/ApproachingEnemyState.h"
#include "ComputerPlayerState/AttackingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath> // sqrt, etc.

ApproachingEnemyState::ApproachingEnemyState(std::shared_ptr<PlayableObject> target)
    : m_target(std::move(target)) {}

void ApproachingEnemyState::enter(ComputerPlayer& player) {
    // player.setAnimation("Run");
}

void ApproachingEnemyState::update(ComputerPlayer& player, float deltaTime) {
    if (!m_target)
        return;

    sf::Vector2f playerPos = player.getPosition();
    PlayableObject* target = player.getTarget();
    sf::Vector2f direction = target->getPosition() - playerPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 100.f) {
        player.changeState(std::make_unique<AttackingState>(m_target));
        return;
    }

    // Normalize direction
    if (distance != 0) {
        direction /= distance;
    }

    // Move toward enemy
    float speed = player.getSpeed(); 
    player.move(direction * speed * deltaTime);
}

void ApproachingEnemyState::exit(ComputerPlayer& player) {
    // Optional: stop movement, reset animation, etc.
}
