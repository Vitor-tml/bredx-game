#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation();

    void addFrame(const sf::IntRect& rect);
    void setSpriteSheet(const sf::Texture& texture);
    void setFrameDuration(float duration);
    void setLooping(bool loop);

    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite) const;

private:
    std::vector<sf::IntRect> frames;
    const sf::Texture* spriteSheet;
    float frameDuration;
    float elapsedTime;
    std::size_t currentFrame;
    bool isLooping;
};

#endif // ANIMATION_H
