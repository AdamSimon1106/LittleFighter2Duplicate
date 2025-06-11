#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation();
    Animation(const sf::Texture* texture, int x, int y, int width, int height, int frameCount, float frameTime, bool loop = true);

    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite) const;
    void reset();

private:
    const sf::Texture* texture;
    int x, y, width, height;
    int frameCount;
    float frameTime;
    float elapsedTime;
    int currentFrame;
    bool looping;
    bool finished;
    int direction = 1;
};
