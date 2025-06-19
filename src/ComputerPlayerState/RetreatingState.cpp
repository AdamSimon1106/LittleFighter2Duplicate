//#include "ComputerPlayerState/RetreatingState.h"
//#include "GamePlay/ComputerPlayer.h"
//#include "ComputerPlayerState/IdleState.h"
//#include <SFML/System/Vector2.hpp>
//
//RetreatingState::RetreatingState() = default;
//
//void RetreatingState::enter(ComputerPlayer& player) {
//    std::cout << "enter:: RetreatingState\n";
//
//    Animation retreatingAnim(player.getTexture(),
//        0, 0,          // x, y
//        80, 80,        // width, height
//        4,             // מספר פריימים
//        0.2f);         // זמן בין פריימים
//
//    player.setAnimation(retreatingAnim);
//    //player.setDiraction(m_input);     m_elapsedTime = 0.f;
//}
//
//void RetreatingState::update(ComputerPlayer& player, float deltaTime) {
//    m_elapsedTime += deltaTime;
//
//    // Move away from nearest visible threat (for now just move left/up)
//    // You can enhance this to analyze real threats nearby
//    sf::Vector2f retreatDirection(-1.f, -1.f);
//    player.move(retreatDirection * player.getSpeed() * deltaTime);
//
//    if (m_elapsedTime >= m_retreatDuration) {
//        // Done retreating — return to idle (or other smart decision)
//        player.changeState(std::make_unique<IdleState>());
//    }
//}
//
//void RetreatingState::exit(ComputerPlayer& player) {
//    // Cleanup if needed
//}
