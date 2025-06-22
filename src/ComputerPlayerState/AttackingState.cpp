//#include "ComputerPlayerState/AttackingState.h"
//#include "ComputerPlayerState/ApproachingEnemyState.h"
//#include "GamePlay/ComputerPlayer.h"
//#include "Objects/PlayableObject.h"
//#include <cmath>
//
//AttackingState::AttackingState(std::shared_ptr<PlayableObject> target)
//    : m_target(std::move(target)) {}
//
//void AttackingState::enter(ComputerPlayer& player) {
//    player.setAnimation("Attack");
//    m_attackCooldown = 0.f; // Start immediately
//}
//
//void AttackingState::update(ComputerPlayer& player, float deltaTime) {
//    if (!m_target)
//        return;
//
//    sf::Vector2f playerPos = player.getPosition();
//    sf::Vector2f targetPos = m_target->getPosition();
//
//    float distance = std::sqrt(std::pow(playerPos.x - targetPos.x, 2) +
//        std::pow(playerPos.y - targetPos.y, 2));
//
//    // Check if still in attack range
//    const float attackRange = 100.f;
//    if (distance > attackRange) {
//        // Too far — switch back to approach state
//        player.changeState(std::make_unique<ApproachingEnemyState>(m_target));
//        return;
//    }
//
//    // Countdown attack cooldown
//    if (m_attackCooldown > 0.f) {
//        m_attackCooldown -= deltaTime;
//        return;
//    }
//
//    // Perform attack
//    player.performAttack(*m_target);
//
//    // Reset cooldown
//    m_attackCooldown = 1.0f; // One second between attacks
//}
//
//void AttackingState::exit(ComputerPlayer& player) {
//    // Stop attack animation or cleanup if needed
//}
