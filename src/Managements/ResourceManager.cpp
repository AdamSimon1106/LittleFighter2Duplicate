#include "Management/ResourceManager.h"

/* static */ ResourceManager& ResourceManager::instance()
{
    static ResourceManager s_instance;   // Constructed on first use, destroyed on exit.
    return s_instance;
}

const sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end())
        return *it->second;
    if (!loadTexture(name))
        throw std::runtime_error("Failed to load texture: " + name);
    return *m_textures.at(name);
}

const sf::Texture& ResourceManager::getAnimationSheet(const std::string& name) {
    auto it = m_animationSheets.find(name);
    if (it != m_animationSheets.end())
        return *it->second;
    // Assuming loadAnimationSheet is similar to loadTexture
    if (!loadTexture(name))  // You’ll need to implement this like loadTexture
        throw std::runtime_error("Failed to load animation sheet: " + name);
    return *m_animationSheets.at(name);
}

const sf::SoundBuffer& ResourceManager::getSoundEffect(const std::string& name) {
    auto it = m_soundEffects.find(name);
    if (it != m_soundEffects.end())
        return *it->second;
    if (!loadSoundEffect(name))
        throw std::runtime_error("Failed to load sound effect: " + name);
    return *m_soundEffects.at(name);
}

sf::Music& ResourceManager::getMusic(const std::string& name) {
    auto it = m_music.find(name);
    if (it != m_music.end())
        return *it->second;
    if (!loadMusic(name))
        throw std::runtime_error("Failed to load music: " + name);
    return *m_music.at(name);
}

const sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = m_fonts.find(name);
    if (it != m_fonts.end())
        return *it->second;
    if (!loadFont(name))
        throw std::runtime_error("Failed to load font: " + name);
    return *m_fonts.at(name);
}

bool ResourceManager::loadTexture(const std::string& name) {
    auto texture = std::make_unique<sf::Texture>();
    std::string path = "resources/textures/" + name + ".png";
    if (!texture->loadFromFile(path))
        return false;
    m_textures.emplace(name, std::move(texture));
    return true;
}

bool ResourceManager::loadSoundEffect(const std::string& name) {
    auto sound = std::make_unique<sf::SoundBuffer>();
    std::string path = "resources/sounds/" + name + ".wav";
    if (!sound->loadFromFile(path))
        return false;
    m_soundEffects.emplace(name, std::move(sound));
    return true;
}

bool ResourceManager::loadMusic(const std::string& name) {
    auto music = std::make_unique<sf::Music>();
    std::string path = "resources/music/" + name + ".ogg";
    if (!music->openFromFile(path))
        return false;
    m_music.emplace(name, std::move(music));
    return true;
}

bool ResourceManager::loadFont(const std::string& name) {
    auto font = std::make_unique<sf::Font>();
    std::string path = "resources/fonts/" + name + ".ttf";
    if (!font->loadFromFile(path))
        return false;
    m_fonts.emplace(name, std::move(font));
    return true;
}

void ResourceManager::clear()
{
    m_textures.clear();
}
