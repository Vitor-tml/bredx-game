#include "Player.h"

Player::Player(sf::Texture& textura, int x, int y, int life, int atack, int points)
       :Character(textura, x, y,  life, atack)
{
    pontos = points;
    velocidadeHorizontal = 200.f;
    
    idleAnimation.setSpriteSheet(gRecursos->getTexture("animacao"));
    walkAnimation.setSpriteSheet(gRecursos->getTexture("animacao"));

    idleAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
    idleAnimation.setFrameDuration(0.1f);
    
    walkAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
    walkAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
    walkAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
    walkAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
    walkAnimation.setFrameDuration(0.05f);

    currentAnimation = &idleAnimation;
    // ==== Caso precise mudar tamanho do sprite
    // setSize(sf::Vector2f(64, 64));
    // sf::FloatRect oldSize =  getHitBox().getGlobalBounds();
    // sf::Vector2f newSize(50, 64);

    // setHitBoxSize(newSize);
    // sf::Vector2f hitBoxOffset = sf::Vector2f((oldSize.width - newSize.x) / 2, oldSize.height - (newSize.y + 5));
    // setHitBoxOffset(hitBoxOffset);
}

void Player::executar(float deltaTime)
{
    velocidade.x = 0.f; // Reseta a velocidade horizontal para não ter aceleração infinita
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocidade.x -= velocidadeHorizontal; // Mover para a esquerda
        setSize(sf::Vector2f(-64, 64));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocidade.x += velocidadeHorizontal;  // Mover para a direita
        setSize(sf::Vector2f(64, 64));
    }

    // // Debug sem gravidade
    // velocidade.y = 0.f;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    //     velocidade.y -= velocidadeHorizontal;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    //     velocidade.y += velocidadeHorizontal;
    // }

    // Verifica a entrada do teclado para pular
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pular(); // atualizar essa função
    }

    isMoving = (velocidade.x != 0)? 1 : 0;
    currentAnimation = (isMoving)? &walkAnimation : &idleAnimation;
    currentAnimation->update(deltaTime);
    currentAnimation->applyToSprite(sprite);

    Character::executar(deltaTime); // Chama o executar da classe pai que aplica a movimentação
}

void Player::pular()
{
    fisica.pular();
}