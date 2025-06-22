//// RisingPhase.cpp
//#include "PlayerStates/JumpBasePhase/RisingPhase.h"
//#include "PlayerStates/JumpBasePhase/HangingPhase.h"
//#include "GamePlay/Player.h"
//
//RisingPhase::RisingPhase(float duration, float speed, float groundY)
//    : m_duration(duration), m_speed(speed), m_groundY(groundY) {
//    m_clock.restart();
//}
//
//std::unique_ptr<JumpPhaseBase> RisingPhase::update(Player& player, float dt) {
//    auto pos = player.getPosition();
//    pos.y -= m_speed * dt;
//    player.setPosition(pos);
//
//    if (m_clock.getElapsedTime().asSeconds() >= m_duration)
//    {
//        std::cout << "in Jumping::update, m_clock.getElapsedTime().asSeconds() >= m_duration\n";
//        return std::make_unique<HangingPhase>(0.2f, m_groundY);
//
//
//    }
//
//    return nullptr;
//}