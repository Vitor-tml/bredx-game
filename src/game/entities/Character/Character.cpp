#include "Character.h"

Character::Character(sf::Texture &textura, int x, int y,  int life, int atack)
          :Entity(textura, x, y)
{
    vida = life;
    ataque = atack;
}
void Character::executar(float deltaTime)
{
    // Executa lógica padra para toda entidade;
    Entity::executar(deltaTime);
}
