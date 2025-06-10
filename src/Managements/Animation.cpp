
#include "Management/Animation.h"

Animation::Animation()
    : texture(nullptr), frameTime(0), elapsedTime(0), currentFrame(0), looping(true), finished(false) {}

Animation::Animation(const sf::Texture* texture, sf::IntRect startRect, sf::IntRect endRect, float frameTime, bool loop)
    : texture(texture), frameTime(frameTime), elapsedTime(0), currentFrame(0), looping(loop), finished(false) {

    // חישוב פריימים לפי טווח
    for (int x = startRect.left; x <= endRect.left; x += startRect.width) {
        frames.emplace_back(x, startRect.top, startRect.width, startRect.height);
    }
}

void Animation::update(float deltaTime) {
    if (finished || frames.empty()) return;

    elapsedTime += deltaTime;
    while (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrame += direction;

        if (currentFrame >= frames.size()) {
            currentFrame = frames.size() - 2;
            direction = -1;
        }
        else if (currentFrame < 0) {
            currentFrame = 1;
            direction = 1;
        }

        if (!looping && (currentFrame == frames.size() - 1 || currentFrame == 0)) {
            finished = true;
            break;
        }
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) const {
    if (texture)
        sprite.setTexture(*texture);
    if (!frames.empty())
        sprite.setTextureRect(frames[currentFrame]);
}

void Animation::reset() {
    currentFrame = 0;
    elapsedTime = 0.f;
    finished = false;
}
