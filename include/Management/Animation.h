#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation();
    Animation(const sf::Texture* texture, sf::IntRect startRect, sf::IntRect endRect, float frameTime, bool loop = true);

    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite) const;
    void reset();

private:
    const sf::Texture* texture;
    std::vector<sf::IntRect> frames;
    float frameTime;
    float elapsedTime;
    size_t currentFrame;
    bool looping;
    bool finished;
    int direction = 1;

};
