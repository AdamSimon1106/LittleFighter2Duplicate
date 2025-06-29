#include "ComputerPlayerState/IdleState.h"
#include "GamePlay/ComputerPlayer.h"
#include "ComputerPlayerState/ApproachingEnemyState.h" // the next state
#include <cmath> // distance calculation
#include "ComputerPlayerState/PickingUpItemState.h"

void IdleState::enter(ComputerPlayer& player) {
    // Optional: reset animation or internal timer
    // player.setAnimation("Idle");
    std::cout << player.getName() << "enter:: IdleState\n";

    //Animation idleAnim(player.getTexture(),
    //    0, 0,          // x, y
    //    80, 80,        // width, height
    //    4,             // מספר פריימים
    //    0.2f);         // זמן בין פריימים

    //player.setAnimation(idleAnim);
    player.setAniName("standing");
    //player.setDiraction(m_input); 
}

void IdleState::update(ComputerPlayer& player, float deltaTime) {
    //// 1. Scan for closest enemy (pseudo code)
    //auto enemies = player.getKnownEnemies();
    //float closestDist = std::numeric_limits<float>::max(); // init to largest float number
    PlayableObject* closestEnemy = nullptr;
    std::shared_ptr<PickableObject> closestObject = nullptr;
    //for (const auto& enemy : enemies) {
    //    float dist = distance(player.getPosition(), enemy->getPosition());
    //    if (dist < closestDist) {
    //        closestDist = dist;
    //        closestEnemy = enemy;
    //    //}

    closestObject = player.getObject();
    closestEnemy = player.getTarget();
    if (closestObject)
    {
        player.changeState(std::make_unique<PickingUpItemState>(closestObject));
    }

 /*   if (closestEnemy)
        std::cout << player.getName() << "[IdleState] Update, target: "  << std::endl;
    else
        std::cout << "THERE IS NO TARGET YET\n";*/

    // 2. If enemy is close enough, change to Approaching state
    else if (closestEnemy) { // threshold distance
        std::cout << "ENEMY FOUND!" << std::endl;

        player.changeState(std::make_unique<ApproachingEnemyState>(closestEnemy));
    }

    // 3. Otherwise, stay idle
}

void IdleState::exit(ComputerPlayer& player) {
    // Optional: stop idle animation, log transition, etc.
}
