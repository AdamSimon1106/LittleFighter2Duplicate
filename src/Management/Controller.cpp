#include "Management/Controller.h"
#include "Management/CollisionHandling.h"
#include "Gameplay/Level.h"
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <utility>
#include <memory>
#include <iostream>
#include <random>


Controller::Controller(sf::RenderWindow& window,
    std::unique_ptr<Level> level,
    std::vector<std::shared_ptr<Player>> players,
    std::vector<std::shared_ptr<Ally>> allies)
    : m_window(window),
    m_level(std::move(level)),
    m_players(std::move(players)),
    m_allies(std::move(allies)),
    m_stats(HUD(window.getSize(), getPlayerAndAllies()))
{   
    m_numOfLevels = ResourceManager::instance().getNumOfLevels();
    m_enemies = m_level->getAllEnemies();
    m_objQueue = m_level->getAllObjects();
    transferNextPickable();
    updateComputerPlayerStats();


    std::vector<std::shared_ptr<PlayableObject>> members;
    for (const auto& p : m_players) {
        members.push_back(p); // implicit upcast is OK here
    }
  
}

void Controller::handleInput(sf::Event ev)
{
    for (auto& player : m_players)
    {
        player->handleInput(ev);
    }
}

void Controller::updateWorld(float deltaTime)
{

    //===========================================
    //===== MOVE INSIDE FUNC ====================
    if (m_waitingForNextWave) {
        m_DelayTimer += deltaTime;
        if (m_DelayTimer >= WAVE_DELAY) {
            m_waitingForNextWave = false;
            m_DelayTimer = 0.f;
            launchNextStage();
        }
    }
    else if (m_waitingForNextLevel) {
        m_DelayTimer += deltaTime;
        if (m_DelayTimer >= LEVEL_DELAY) {
            m_waitingForNextLevel = false;
            m_DelayTimer = 0.f;
            launchNextLevel();
        }
    }
    else if (m_needToWaitForKnocked) {
        m_DelayTimer += deltaTime;
        if (m_DelayTimer >= KNOCKED_CHECK_DELAY) {
            m_canMoveStage = true;
            m_needToWaitForKnocked = false;
            m_DelayTimer = 0.f;

        }
    }
    else if (m_enemies.empty() && m_canMoveStage) {
        m_canMoveStage = false;
        if (m_nextStageIndex < m_level->numOfStages()) { // V
            m_waitingForNextWave = true;
            m_DelayTimer = 0.f;
            m_nextStageIndex++;
        }
        else if (m_nextLevelIndex < m_numOfLevels) { // V
            
            m_waitingForNextLevel = true;
            m_nextStageIndex = 1;
            m_DelayTimer = 0.f;
        }
        else {
            m_playerWon = true;
        }
    }
    else if (m_enemies.empty()) {
        m_needToWaitForKnocked = true;
    }
    //===========================================

    for (auto& player : m_players)
    {
        player->update(deltaTime);
        m_level->handleCollisionsWithPlayer(*player); 

    }

    for (auto& ally : m_allies)
    {

       ally->update(deltaTime);
       m_level->handleCollisionsWithPlayer(*ally);

    }
    for (auto& enemy : m_enemies)
    {
        enemy->update(deltaTime);
        m_level->handleCollisionsWithPlayer(*enemy);
		checkCollisions(enemy);

    }
    for (auto& obj : m_pickables)
    {
        obj->update(deltaTime);
		
		
    }
	m_level->update(deltaTime);
    std::erase_if(m_pickables, [](std::shared_ptr<PickableObject>& obj) {
        return obj->isUsed();
        });

    for (auto& dead : m_deads)
    {
        dead->update(deltaTime);
    }


    
  
    updateComputerPlayerStats();

    for (int i = 0; i < m_players.size(); i++) {
        std::shared_ptr<Player> player = m_players[i];
        if (!player)
            continue;
        if (!player->getState()->isAccessible()) {
            removeAccess(player, m_players);
            i--;
        }
    }

    m_objectTimer += deltaTime;
    if (m_newObjectCoolDown <= m_objectTimer) {
        m_objectTimer = 0.f;
        transferNextPickable();
    }


    m_stats.update(getPlayerAndAllies(), m_enemies ,getLevelInfo());

    if(m_players.size())
        m_level->handleCollisionsWithPlayer(*m_players.back()); 


}


void Controller::checkLevelEndConditions()
{
    if (m_level->areAllEnemiesDefeated())
    {
        m_levelFinished = true;
        m_playerWon = true;
        return;
    }

    bool allPlayersDefeated = true;
    for (const auto& player : m_players)
    {
        if (player->isAlive())  
        {
            allPlayersDefeated = false;
            break;
        }
    }
    for (const auto& ally : m_allies)
    {
        if (ally->isAlive())
        {
            allPlayersDefeated = false;
            break;
        }
    }

    if (allPlayersDefeated)
    {
        m_levelFinished = true;
        m_playerWon = false;
    }
}

void Controller::render()
{
    // Draw background, enemies, pickable objects, etc.
    m_level->render(m_window);

    for (const auto& dead : m_deads)
    {
        dead->draw(m_window);

    }
    for (const auto& obj : m_pickables) {
        obj->draw(m_window);
    }


    for (const auto& player : m_players)
    {
        player->draw(m_window);
    }

  
    for (const auto& ally : m_allies)
    {
        ally->draw(m_window);
    }
    


    for (const auto& enemy : m_enemies)
    {
        enemy->draw(m_window);
    }

    if (m_waitingForNextWave) {

        printStageAlert("Stage: " + std::to_string(m_nextStageIndex));
    }
    if (m_waitingForNextLevel) {

        printStageAlert("New level!\n strating level " + std::to_string(m_nextLevelIndex + 1) + ".");
    }
    if (m_playerWon)
    {
        printStageAlert("Congratulations! \n YOU WON!");
    }
	m_stats.draw(m_window);


            
}

void Controller::setPlayer(PlayerData player)
{
    m_players.push_back(std::make_shared<Player>(player));
  
}

void Controller::setAlly(std::shared_ptr<Ally> ally)
{
	if (ally) {
		m_allies.push_back(ally);
	}
	else {
		std::cerr << "Error: Attempted to add a null ally." << std::endl;
	}
}



void Controller::launchNextStage()
{
    if (m_nextStageIndex <= m_level->numOfStages()) {
        std::erase_if(m_deads, [](const std::shared_ptr<PlayableObject>& obj) {
            return dynamic_cast<Enemy*>(obj.get()) != nullptr;
            });
        m_enemies = m_level->getAllEnemies();
    }

}

void Controller::launchNextLevel()
{
    if (m_nextLevelIndex <= m_numOfLevels) {
        std::erase_if(m_deads, [](const std::shared_ptr<PlayableObject>& obj) {
            return dynamic_cast<Enemy*>(obj.get()) != nullptr;
            });
        resetPlayersStats();
        m_level = ResourceManager::instance().getLevel(m_nextLevelIndex);
        m_nextLevelIndex++;
        m_enemies = m_level->getAllEnemies();
        m_objQueue = m_level->getAllObjects();
    }

}

// Responsibile for target & safe zone assignment, death handling. 
// (for each of the computer players)
void Controller::updateComputerPlayerStats() {

    updateStats(m_allies, m_enemies);
    updateStats(m_enemies, m_allies, m_players);
    restoreKnockedAccess();


}

//======================================
//======= NOT SURE IF NEEDED ===========
bool Controller::isLevelFinished() const
{
    return m_levelFinished;
}

bool Controller::didWin() const
{
    return m_playerWon;
}
//======================================


// Calculates the Euclidean distance between two 2D points
float Controller::distanceBetween(sf::Vector2f a, sf::Vector2f b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}



void Controller::restoreKnockedAccess() {
    auto it = m_deads.begin();
    while (it != m_deads.end()) {
        auto& disabled = *it;
        if (disabled->getState()->isAccessible()) {
            bool restored = false;

            if (auto enemy = std::dynamic_pointer_cast<Enemy>(disabled)) {
                m_enemies.push_back(enemy);
                restored = true;
            }
            else if (auto player = std::dynamic_pointer_cast<Player>(disabled)) {
                m_players.push_back(player);
                restored = true;
            }
            else if (auto ally = std::dynamic_pointer_cast<Ally>(disabled)) {
                m_allies.push_back(ally);
                restored = true;
            }

            if (restored) {
                it = m_deads.erase(it);
                continue;
            }
        }

        ++it; 
    }
}

void Controller::checkCollisions(std::shared_ptr<Enemy> enemy)
{
    checkCollisionsWithPlayers(enemy);
    checkCollisionsWithAllies(enemy);
}

void Controller::checkCollisionsWithAllies(std::shared_ptr<Enemy> enemy)
{
    for (auto& ally : m_allies) {
        if (ally->collide(*enemy))
        {
            processCollision(*ally, *enemy);
			processCollision(*enemy, *ally);
        }
    }
}

void Controller::checkCollisionsWithPlayers(std::shared_ptr<Enemy> enemy)
{
	for (auto& player : m_players) {
        if (player->collide(*enemy))
        {
            enemy->setXHit(player->getDirection());
            processCollision(*player, *enemy);
			processCollision(*enemy, *player);
        }
	}
}
std::vector<std::shared_ptr<PlayableObject>> Controller::getPlayerAndAllies() {
    std::vector<std::shared_ptr<PlayableObject>> result;
    for (const auto& p : m_players)
        result.push_back(std::static_pointer_cast<PlayableObject>(p));
    for (const auto& a : m_allies)
        result.push_back(std::static_pointer_cast<PlayableObject>(a));
    
    return result;
}

void Controller::resetPlayersStats()
{
    bringPlayersBack();

    for (auto& player : m_players) {
        player->resetHP();
        player->setPosition(getRandomYPosition(50, 380, 800));
    }
    for (auto& ally : m_allies) {
        ally->resetHP();
        ally->setPosition(getRandomYPosition(50, 380, 800));
    }
}

std::string Controller::getLevelInfo() const
{
    std::string amountOfLevels = std::to_string(m_numOfLevels);
    std::string currLevel = std::to_string(m_nextStageIndex);
    return currLevel + " - " + amountOfLevels;
}


void Controller::printStageAlert(const std::string& message) {

    static sf::Font font;
    static bool loaded = false;
    if (!loaded) {
        if (!font.loadFromFile("resources/Fonts/lesterbold.ttf"))
            return;
        loaded = true;
    }
    sf::Text alert;
    alert.setFont(font);
    alert.setString(message);
    alert.setCharacterSize(64); 
    alert.setFillColor(sf::Color::White); 
    alert.setOutlineColor(sf::Color::Black);
    alert.setOutlineThickness(4.f);

   
    sf::FloatRect bounds = alert.getLocalBounds();
    alert.setOrigin(bounds.width / 2, bounds.height / 2);
    alert.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 4.f); 

    m_window.draw(alert);
}

void Controller::bringPlayersBack() {
        for (auto& dead : m_deads) {
            dead->resetHP();
            if (auto player = std::dynamic_pointer_cast<Player>(dead)) {
                player->setState(std::make_unique<StandingState>(Input::NONE));
            }
            else if (auto ally = std::dynamic_pointer_cast<Ally>(dead)) {
                ally->setState(std::make_unique<IdleState>());
            }
        }
}


sf::Vector2f Controller::getRandomYPosition(float xPos, float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    float y = dist(gen);
    return sf::Vector2f(xPos, y);
}

void Controller::transferNextPickable() {
    if (!m_objQueue.empty()) {
        m_pickables.push_back(std::move(m_objQueue.back()));
        m_objQueue.pop_back();
    }
}
