#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

struct PlayerData; 
class Level;

struct AssetMeta {
    std::string name;
    enum class Type {Texture,AnimationSheet,SoundEffect,Music,Font} type;
};

class ResourceManager {
public:
    // Singleton.
    static ResourceManager& instance();

    // Deleted copy/move semantics – only one instance can ever exist.
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    // Returns an immutable reference to the requested texture.
    const sf::Texture& getTexture(const std::string& name);
    const sf::Texture& getAnimationSheet(const std::string& name);
    const sf::SoundBuffer& getSoundEffect(const std::string& name);
    sf::Music& getMusic(const std::string& name);
    const sf::Font& getFont(const std::string& name);
    const std::shared_ptr<PlayerData> getPlayerData(const std::string& name) const;
    std::unique_ptr<Level> getLevel(const int index);
    int getNumOfLevels();
    const std::vector<std::pair<std::string, std::shared_ptr<PlayerData>>>& getCharacters() const;
    void loadCharacterData(const std::shared_ptr<PlayerData> p);
    void loadCurrentLevel(std::unique_ptr<Level> level);

    // Frees all 
    // ed textures – call on shutdown or when reloading a level.
    void clear();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    bool loadTexture(const std::string& name);
    bool loadSoundEffect(const std::string& name);
    bool loadMusic(const std::string& name);
    bool loadFont(const std::string& name);
    std::vector<std::pair<std::string, std::shared_ptr<PlayerData>>> m_characters;
    std::vector<std::unique_ptr<Level>> m_levels;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_animationSheets;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_soundEffects;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
};
