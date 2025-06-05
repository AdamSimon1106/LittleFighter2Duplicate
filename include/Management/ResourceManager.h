#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>


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
    const sf::Texture& getTexture(const std::string& id,
        const std::string& filePath);

    // Optional explicit unloading (rarely needed in most games).
    void unloadTexture(const std::string& id);

    // Frees all loaded textures – call on shutdown or when reloading a level.
    void clear();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};
