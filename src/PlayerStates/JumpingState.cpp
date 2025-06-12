#include "PlayerStates/JumpingState.h"
#include"PlayerStates/StandingState.h"

#include "GamePlay/Player.h"

JumpingState::JumpingState(Input input)
{
    m_input = input;
}

std::unique_ptr<PlayerBaseState> JumpingState::handleInput(Input input)
{

    std::cout << input << std::endl;
    

    return nullptr;
}

void JumpingState::enter(Player& player)
{
	std::cout << "enter:: JumpingState\n";
    
    Animation jumpingAnim(player.getTexture(),
        0, 160,       // x, y – נניח שזו שורת הקפיצה
        80, 80,       // width, height
        2,            // 2 פריימים בקפיצה לדוגמה
        0.25f);       // קצב איטי יותר

    player.setAnimation(jumpingAnim);
    player.setDiraction(m_input);

    m_clock.restart();
}

void JumpingState::update(Player& player, float dt)
{
    std::cout << m_clock.getElapsedTime().asSeconds() << " " << m_duration << '\n';
    
    if (m_clock.getElapsedTime().asSeconds() >= m_duration)
    {
        std::cout << "in jumping to standing\n";
        player.setDiraction(m_input);
        player.setState(std::make_unique<StandingState>(m_input));
    }
    
}



