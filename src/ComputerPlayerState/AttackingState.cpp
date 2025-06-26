#include "ComputerPlayerState/AttackingState.h"
#include "ComputerPlayerState/ApproachingEnemyState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include <cmath>

AttackingState::AttackingState(PlayableObject* target)
    : m_target(std::move(target)) {}

void AttackingState::enter(ComputerPlayer& player) {
    std::cout << "enter:: AttackingState\n";

    //Animation attackingAnim(player.getTexture(),
    //    80, 0,          // x, y
    //    80, 80,        // width, height
    //    6,             // מספר פריימים
    //    0.2f);         // זמן בין פריימים

    //player.setAnimation(attackingAnim);
    player.setAniName("attacking");
    m_target = player.getTarget();
    m_target->attack();
    // I think we need switch-case here according to the attack
    //player.setDiraction(m_input);     m_attackCooldown = 0.f; // Start immediately
}

void AttackingState::update(ComputerPlayer& player, float deltaTime) {
    if (!m_target)
        return;
    //std::cout << player.getName() <<" - MY TARGET NAME IS: " << m_target->getName() << std::endl;
    player.setAniName("attacking");

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f targetPos = m_target->getPosition();
 

    float distance = std::sqrt(std::pow(playerPos.x - targetPos.x, 2) +
        std::pow(playerPos.y - targetPos.y, 2));
    std::cout << targetPos.x << std::endl;
    std::cout << "[AttackingState] " << player.getName() << " distance to " << m_target->getName() << ":" << distance << std::endl;

    // Check if still in attack range
    const float attackRange = 150.f;
    if (distance > attackRange) {
        // Too far — switch back to approach state
        player.changeState(std::make_unique<ApproachingEnemyState>(m_target));
        return;
    }



    // Countdown attack cooldown
    if (m_attackCooldown > 0.f) {
        m_attackCooldown -= deltaTime;
        return;
    }

    // Perform attack
    player.performAttack(*m_target);

    // Reset cooldown
    m_attackCooldown = 1.0f; // One second between attacks
}

void AttackingState::exit(ComputerPlayer& player) {
    // Stop attack animation or cleanup if needed
}
