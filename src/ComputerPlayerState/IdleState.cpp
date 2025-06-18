//#include "ComputerPlayerState/IdleState.h"
//#include "GamePlay/ComputerPlayer.h"
//#include "ComputerPlayerState/ApproachingEnemyState.h" // the next state
//#include <cmath> // distance calculation
//
//void IdleState::enter(ComputerPlayer& player) {
//    // Optional: reset animation or internal timer
//    // player.setAnimation("Idle");
//}
//
//void IdleState::update(ComputerPlayer& player, float deltaTime) {
//    //// 1. Scan for closest enemy (pseudo code)
//    //auto enemies = player.getKnownEnemies();
//    //float closestDist = std::numeric_limits<float>::max(); // init to largest float number
//    PlayableObject* closestEnemy = nullptr;
//
//    //for (const auto& enemy : enemies) {
//    //    float dist = distance(player.getPosition(), enemy->getPosition());
//    //    if (dist < closestDist) {
//    //        closestDist = dist;
//    //        closestEnemy = enemy;
//    //    }
//    //}
//    closestEnemy = player.getTarget();
//
//    // 2. If enemy is close enough, change to Approaching state
//    if (closestEnemy) { // threshold distance
//        player.changeState(std::make_unique<ApproachingEnemyState>(closestEnemy));
//    }
//
//    // 3. Otherwise, stay idle
//}
//
//void IdleState::exit(ComputerPlayer& player) {
//    // Optional: stop idle animation, log transition, etc.
//}
