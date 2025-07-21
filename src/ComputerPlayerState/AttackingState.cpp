#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/PickingUpItemState.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "GamePlay/ComputerPlayer.h"
#include "Objects/PlayableObject.h"
#include "EventCommands/HandsAttackCommand.h"
#include <memory>
#include <cmath>

AttackingState::AttackingState(std::shared_ptr<Object> target)
    : m_target(std::move(target)) {
    m_attackCooldown = ATTACK_COOLDOWN; 
}

void AttackingState::enter(PlayableObject& player) {
    std::cout << "im in AttackingState::enter\n";
    player.setAniName("attacking");
    player.attack();
    player.adjustRange(HANDS_ATTACK_RANGE);
    player.setStrategyName("");
    player.wantItem();
    player.startAttackTimer();
    
}

void AttackingState::update(PlayableObject& player, float deltaTime) {
    //std::cout << "canAttack: " << player.canAttack() << "\n";

    if (player.canAttack()) {
        if (!m_target)
            return;

        if (!player.getTarget()) {
            player.setState(std::make_unique<IdleState>());
            return;
        }
        if (auto enemy = std::dynamic_pointer_cast<PlayableObject>(m_target)) {
            if (!enemy->getState()->isAccessible()) {
                m_target = player.getTarget();
            }
        }

        player.setAniName("attacking");

        sf::Vector2f playerPos = player.getPosition();

        sf::Vector2f targetPos = m_target->getPosition();


        float distance = std::sqrt(std::pow(playerPos.x - targetPos.x, 2) +
            std::pow(playerPos.y - targetPos.y, 2));

        if (distance > player.getAttackRange()) {
            // Too far — switch back to approach state
            player.setState(std::make_unique<ApproachingEnemyState>(m_target));
            return;
        }


        // Countdown attack cooldown
        if (m_attackCooldown > 0) {
            m_attackCooldown -= deltaTime;
            return;
        }
    }

}

void AttackingState::exit(ComputerPlayer& player) {
}



void AttackingState::name() {
}

void AttackingState::onHandsAttack(PlayableObject& player)
{
    player.setState(std::make_unique<BlockingState>());
}
void AttackingState::onStoneHit(PlayableObject& player) {
	player.setState(std::make_unique<GotHitState>());

}
void AttackingState::onExplosion(PlayableObject& player) {


}

void AttackingState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedDownState>());
}
