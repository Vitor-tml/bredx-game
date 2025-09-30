#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y) : Ente(),
                               fisica(&posicao, &velocidade),
                               hitBoxSize(sf::Vector2f(0.f, 0.f)),
                               hitBoxOffset(sf::Vector2f(0.f, 0.f))
{
    colisao = 0;
    setOrigin(); // Isso serve para todas as entidades? ou só para as que se movem?
    posicao = sf::Vector2f(x, y);
    setPosicao(posicao);
    criarHitBox(); // Inicializa a hitbox
}

Entity::Entity(sf::Texture &textura, int x, int y, bool colide) : Ente(textura),
                                                     hitBox(sf::Vector2f(0.f, 0.f)),
                                                     fisica(&posicao, &velocidade),
                                                     colisao(colide)
                                                
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
    setPosicao(posicao);
    criarHitBox(); // Inicializa a hitbox
}

void Entity::setOrigin()
{
    // Origem embaixo no meio
    sf::FloatRect tamanho = sprite.getGlobalBounds();
    sprite.setOrigin(tamanho.width / 2, tamanho.height);
}
void Entity::setPosicao(int x, int y)
{
    posicao = sf::Vector2f(x, y);
    sprite.setPosition(posicao);
}

void Entity::setPosicao(sf::Vector2f novaPosicao)
{
    posicao = novaPosicao;
    sprite.setPosition(posicao);
}

sf::Vector2f Entity::getPosicao() const
{
    return posicao;
}

sf::RectangleShape &Entity::getHitBox()
{
    return hitBox;
}

void Entity::executar(float deltaTime)
{
    fisica.aplicaFisica(deltaTime);
    sprite.setPosition(posicao);
    atualizaHitBox();
}
void Entity::criarHitBox()
{
    hitBox.setFillColor(sf::Color::Transparent); // Tornar a hitbox visível sem preenchimento
    hitBox.setOutlineColor(sf::Color::Red);      // Cor da borda da hitbox
    hitBox.setOutlineThickness(1.f);             // Espessura da borda

    // Se a hitbox personalizada não for definida, use o tamanho da sprite
    if (hitBoxSize == sf::Vector2f(0.f, 0.f))
        hitBoxSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    // Atualiza o tamanho e a posição da hitbox com base na sprite e offset
    hitBox.setSize(hitBoxSize);
}

void Entity::setHitBoxSize(sf::Vector2f size)
{
    hitBoxSize = size;
    criarHitBox(); // Atualiza a hitbox ao mudar o tamanho
}

void Entity::setHitBoxOffset(sf::Vector2f offset)
{
    hitBoxOffset = offset;
    criarHitBox(); // Atualiza a hitbox ao mudar o offset
}

void Entity::atualizaHitBox()
{
    // Ajustar a posição da hitbox para alinhar corretamente com a sprite
    hitBox.setPosition(sprite.getPosition() - sprite.getOrigin() + hitBoxOffset);
}

void Entity::colidiuComTile(Entity *tile) // Mudar depois para não usar métodos da sprite
{
    // Obtém as bounding boxes das entidades
    sf::FloatRect entidadeBounds = getHitBox().getGlobalBounds();
    sf::FloatRect tileBounds = tile->getHitBox().getGlobalBounds();

    // Calcula a interseção entre as bounding boxes
    sf::FloatRect interseccao;
    if (entidadeBounds.intersects(tileBounds, interseccao))
    {
        // Determina o eixo de menor interseção
        if (interseccao.width < interseccao.height)
        {
            // Colisão horizontal
            if (entidadeBounds.left < tileBounds.left)
            {
                // Colisão pela esquerda do tile
                posicao.x = (tileBounds.left - entidadeBounds.width / 2.0f) + (getOrigin().x - entidadeBounds.width / 2.0f);
            }
            else
            {
                // Colisão pela direita do tile
                posicao.x = (tileBounds.left + tileBounds.width + entidadeBounds.width / 2.0f) - (getOrigin().x - entidadeBounds.width / 2.0f);
            }
            velocidade.x = 0; // Para a velocidade horizontal
        }
        else
        {
            // Colisão vertical
            if (entidadeBounds.top < tileBounds.top) 
            {   // Colisão pelo topo do tile
                // (topo do tile) - (origem da entidade)
                posicao.y = (tileBounds.top - entidadeBounds.height) + (getOrigin().y + 2.f);
                setNoChao(true);
            }
            else
            {
                // Colisão pela base do tile
                posicao.y = (tileBounds.top + tileBounds.height) + entidadeBounds.height;
            }
            velocidade.y = 0; // Para a velocidade vertical
        }

        // Atualiza a posição da sprite e da hitbox
        setPosicao(posicao);
        atualizaHitBox();
    }
}

void Entity::setNoChao(bool noChao)
{
    fisica.setNoChao(noChao);
}

bool Entity::getNoChao() const
{
    return fisica.getNoChao();
}
