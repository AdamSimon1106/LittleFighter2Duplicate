#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Gameplay/Level.h"
#include "Gameplay/Player.h"
#include "Gameplay/Ally.h"
#include "UI/HeadsUpDisplay.h"

class Controller
{
public:
    // Constructor: receives all game data needed to run the battle
    Controller(sf::RenderWindow& window,
        std::unique_ptr<Level> level,
        std::vector<std::shared_ptr<Player>> players,     // human-controlled
        std::vector<std::shared_ptr<Ally>> allies);       // AI-controlled allies

    // Called each frame from InGameState
    void updateAndRender(float deltaTime);

    // ========== Core logic ==========
    void handleInput(sf::Event ev);                  // Input for human-controlled players
    void updateWorld(float deltaTime);   // Updates players, allies, level, etc.
    void checkLevelEndConditions();      // Determines whether the match is over
    void render();

    // Returns whether the level has ended, and who won
    bool isLevelFinished() const;
    bool didWin() const;

private:
    sf::RenderWindow& m_window;
    std::unique_ptr<Level> m_level;
    std::vector<std::shared_ptr<Player>> m_players; // human-controlled
    std::vector<std::shared_ptr<Ally>> m_allies;  // AI-controlled

    // ========== Internal state ==========
    HeadsUpDisplay m_stats;
    bool m_levelFinished = false;
    bool m_playerWon = false;
  // Draws the full scene
};
