//#include "PlayerStates/JumpingState.h"
//#include"PlayerStates/StandingState.h"
//#include "PlayerStates/JumpBasePhase/RisingPhase.h"
//
//#include "GamePlay/Player.h"
//
//JumpingState::JumpingState(Input input)
//{
//    m_input = input;
//}
//
//std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
//{
//
//    std::cout << input << std::endl;
//    
//
//    return nullptr;
//}
//
//void JumpingState::enter(Player& player)
//{
//	std::cout << "enter:: JumpingState\n";
//    
//    Animation jumpingAnim(player.getTexture(),
//        0, 520,       // x, y – נניח שזו שורת הקפיצה
//        80, 80,       // width, height
//        4,            // 2 פריימים בקפיצה לדוגמה
//        0.25f);       // קצב איטי יותר
//
//    player.setAnimation(jumpingAnim);
//    //player.setDiraction(m_input);
//
//    m_groundY = player.getPosition().y;
//    m_phase = std::make_unique<RisingPhase>(0.15f, 650.f, player.getPosition().y);
//}
//
//void JumpingState::update(Player& player, float dt)
//{
//    if (!m_phase) {
//        player.setState(std::make_unique<StandingState>(Input::NONE));
//        return;
//    }
//
//    if (auto next = m_phase->update(player, dt)) {
//        m_phase = std::move(next);
//    }
//    else if (player.getPosition().y >= m_groundY) {
//        player.setState(std::make_unique<StandingState>(Input::NONE));
//    }
//    
//}
//
//
//
