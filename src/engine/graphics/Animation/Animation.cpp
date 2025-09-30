#include "Animation.h"

Animation::Animation() 
    : spriteSheet(nullptr), frameDuration(0.1f), elapsedTime(0.f), currentFrame(0), isLooping(true) {}

void Animation::addFrame(const sf::IntRect& rect) {
    frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture& texture) {
    spriteSheet = &texture;
}

void Animation::setFrameDuration(float duration) {
    frameDuration = duration;
}

void Animation::setLooping(bool loop) {
    isLooping = loop;
}

void Animation::update(float deltaTime) {
    elapsedTime += deltaTime;

    if (elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        if (currentFrame + 1 < frames.size()) {
            currentFrame++;
        } else if (isLooping) {
            currentFrame = 0;
        }
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) const {
    if (spriteSheet) {
        sprite.setTexture(*spriteSheet);
        sprite.setTextureRect(frames[currentFrame]);
    }
}
