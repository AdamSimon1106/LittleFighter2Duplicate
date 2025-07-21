#pragma once

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>


class LevelLoader {
public:
    LevelLoader(std::string indexPath, sf::Vector2f windowSize);
    // Loads the list of level file names from the given index file
    void loadLevelsList();

    // Checks if there is another level available
    bool hasNextLevel() const;

    // Returns the next level file name and advances the index
    std::string getNextLevelFile();

    // Resets to the beginning of the level list
    void reset();

    bool loadNewLevel();

    std::string getCurrentlyLoadingFile() const;

private:
    sf::Vector2f m_levelWindowSize;
    std::string m_indexPath;
    int m_currentIndex = 0;
    std::vector<std::string> m_levelFiles;
    std::string m_currentFile;
};
