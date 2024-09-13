#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y) : 
        Ente(),
        fisica(&posicao, &velocidade),
        hitBoxSize(sf::Vector2f(0.f, 0.f)),
        hitBoxOffset(sf::Vector2f(0.f, 0.f))
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
    criarHitBox();  // Inicializa a hitbox
}

Entity::Entity(sf::Texture &textura, int x, int y) : 
        Ente(textura),
        hitBox(sf::Vector2f(0.f, 0.f)),
        fisica(&posicao, &velocidade)
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
    criarHitBox();  // Inicializa a hitbox
}

void Entity::setOrigin()
{
    // Origem embaixo no meio
    sf::FloatRect tamanho = sprite.getGlobalBounds();
    sprite.setOrigin(tamanho.width/2, tamanho.height);
}
void Entity::setPosicao(int x, int y)
{
    posicao = sf::Vector2f(x, y);
}

void Entity::setPosicao(sf::Vector2f novaPosicao)
{
    posicao = novaPosicao;
}

sf::Vector2f Entity::getPosicao() const
{
    return posicao;
}

void Entity::executar(float deltaTime)
{
    // Movimentação básica para testes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocidade.y = -100.f; // Mover para cima
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocidade.y = 100.f;  // Mover para baixo
    else
        velocidade.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x = -100.f; // Mover para a esquerda
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x = 100.f;  // Mover para a direita
    else
        velocidade.x = 0.f;

    fisica.aplicaFisica(deltaTime);
    sprite.setPosition(posicao);
    atualizaHitBox();
}

void Entity::criarHitBox()
{
    hitBox.setFillColor(sf::Color::Transparent); // Tornar a hitbox visível sem preenchimento
    hitBox.setOutlineColor(sf::Color::Red); // Cor da borda da hitbox
    hitBox.setOutlineThickness(1.f); // Espessura da borda  
    
    // Se a hitbox personalizada não for definida, use o tamanho da sprite
    if (hitBoxSize == sf::Vector2f(0.f, 0.f))
    {
        hitBoxSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    }

    // Atualiza o tamanho e a posição da hitbox com base na sprite e offset
    hitBox.setSize(hitBoxSize);
}

void Entity::setHitBoxSize(sf::Vector2f size)
{
    hitBoxSize = size;
    criarHitBox();  // Atualiza a hitbox ao mudar o tamanho
}

void Entity::setHitBoxOffset(sf::Vector2f offset)
{
    hitBoxOffset = offset;
    criarHitBox();  // Atualiza a hitbox ao mudar o offset
}

void Entity::atualizaHitBox()
{
    hitBox.setPosition(sprite.getPosition() - sf::Vector2f(hitBoxSize.x / 2, hitBoxSize.y) + hitBoxOffset);
}