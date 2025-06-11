
#include "Management/Animation.h"

Animation::Animation()
    : texture(nullptr), x(0), y(0), width(0), height(0), frameCount(0),
    frameTime(0), elapsedTime(0), currentFrame(0), looping(true), finished(false) {}

Animation::Animation(const sf::Texture* tex, int x, int y, int w, int h, int count, float time, bool loop)
    : texture(tex), x(x), y(y), width(w), height(h), frameCount(count),
    frameTime(time), elapsedTime(0), currentFrame(0), looping(loop), finished(false) {}


void Animation::update(float deltaTime) {
    if (finished || frameCount <= 0) return;

    elapsedTime += deltaTime;
    while (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrame += direction;

        if (currentFrame >= frameCount) {
            currentFrame = frameCount - 2;
            direction = -1;
        }
        else if (currentFrame < 0) {
            currentFrame = 1;
            direction = 1;
        }

        if (!looping && (currentFrame == frameCount - 1 || currentFrame == 0)) {
            finished = true;
            break;
        }
    }
}


void Animation::applyToSprite(sf::Sprite& sprite) const {
    if (!texture || frameCount <= 0) return;

    sprite.setTexture(*texture);

    sf::IntRect rect(x + currentFrame * width, y, width, height);
    sprite.setTextureRect(rect);
}

void Animation::reset() {
    currentFrame = 0;
    elapsedTime = 0.f;
    finished = false;
}
