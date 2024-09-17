#include "Player.h"

Player::Player(sf::Texture& textura, int x, int y, int life, int atack, int points)
       :Character(textura, x, y,  life, atack)
{
    pontos = points;
    velocidadeHorizontal = 200.f;
}

void Player::executar(float deltaTime)
{
    velocidade.x = 0.f; // Reseta a velocidade horizontal para não ter aceleração infinita

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x -= velocidadeHorizontal; // Mover para a esquerda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x += velocidadeHorizontal;  // Mover para a direita

    // Verifica a entrada do teclado para pular
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pular(); // atualizar essa função
    }

    Character::executar(deltaTime); // Chama o executar da classe pai que aplica a movimentação
}

void Player::pular()
{
    fisica.pular();
}