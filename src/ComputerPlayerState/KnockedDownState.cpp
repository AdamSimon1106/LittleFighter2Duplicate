//#include "ComputerPlayerState/KnockedDownState.h"
//#include "GamePlay/ComputerPlayer.h"
//#include "ComputerPlayerState/IdleState.h"
//
//KnockedDownState::KnockedDownState() = default;
//
//void KnockedDownState::enter(ComputerPlayer& player) {
//    std::cout << "enter:: KnockedDownState\n";
//
//    Animation knockedDownAnim(player.getTexture(),
//        240, 0,          // x, y
//        80, 80,        // width, height
//        5,             // מספר פריימים
//        0.2f,
//        false);         
//
//    player.setAnimation(knockedDownAnim);
//    //player.setDiraction(m_input);     
//    m_elapsedTime = 0.0f;
//    player.setControllable(false);
//}
//
//void KnockedDownState::update(ComputerPlayer& player, float deltaTime) {
//    m_elapsedTime += deltaTime;
//
//    if (m_elapsedTime >= m_recoveryTime) {
//        player.setControllable(true);
//        player.changeState(std::make_unique<IdleState>());
//    }
//}
//
//void KnockedDownState::exit(ComputerPlayer& player) {
//    player.setControllable(true); // Restore control in any case
//}
