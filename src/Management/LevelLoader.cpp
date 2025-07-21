#include "Management/LevelLoader.h"
#include "Gameplay/Level.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


LevelLoader::LevelLoader(std::string indexPath, sf::Vector2f windowSize) : m_indexPath(indexPath)
{
    m_levelWindowSize = windowSize;
    loadLevelsList();
}

void LevelLoader::loadLevelsList() {
    std::ifstream file(m_indexPath);
    if (!file.is_open()) throw std::runtime_error("Failed to open file: " + m_indexPath);

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            m_levelFiles.push_back(line);
        }
    }

    file.close();
}

bool LevelLoader::hasNextLevel() const {
    return m_currentIndex < m_levelFiles.size();
}

std::string LevelLoader::getNextLevelFile() {
    if (!hasNextLevel())
        return "";

    return m_levelFiles[m_currentIndex++];
}

void LevelLoader::reset() {
    m_currentIndex = 0;
}

bool LevelLoader::loadNewLevel()
{
    if (m_currentIndex == m_levelFiles.size()) return false;
    std::string path = m_levelFiles[m_currentIndex];
    m_currentFile = path;
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("couldn't open file: " + path);

    std::string line;
    bool readingSquads = true;
    auto currentLevelPtr = std::make_unique<Level>("lvl1bg", m_levelWindowSize);
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Objects section inside file
        if (line == "obj") {
            readingSquads = false;
            continue;
        }

        if (readingSquads) {
            currentLevelPtr->addSquad(line);  
        }
        else {
            currentLevelPtr->addPickableObjects(line);
        }
    }
    ResourceManager::instance().loadCurrentLevel(std::move(currentLevelPtr));
    ++m_currentIndex;
    
    file.close();
    return true;
}

std::string LevelLoader::getCurrentlyLoadingFile() const
{
    return m_currentFile;
}