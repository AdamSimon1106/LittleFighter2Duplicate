#include "Management/ResourceManager.h"

/* static */ ResourceManager& ResourceManager::instance()
{
    static ResourceManager s_instance;   // Constructed on first use, destroyed on exit.
    return s_instance;
}

const sf::Texture& ResourceManager::getTexture(const std::string& id)
{

   
    // Already loaded? Just return the cached copy.
    if (auto it = m_textures.find(id); it != m_textures.end())
        return *it->second;

    // Otherwise load from disk.
    std::string filePath ="resources/textures/" + id + ".png";
    auto tex = std::make_unique<sf::Texture>();
    if (!tex->loadFromFile(filePath))
        throw std::runtime_error("ResourceManager: failed to load '" + filePath + '\'');

    const sf::Texture& ref = *tex;           // Keep a reference before move.
    m_textures.emplace(id, std::move(tex));  // Store in the map.
    return ref;
}

void ResourceManager::unloadTexture(const std::string& id)
{
    m_textures.erase(id);   // GPU memory freed when unique_ptr leaves scope.
}

void ResourceManager::clear()
{
    m_textures.clear();
}
