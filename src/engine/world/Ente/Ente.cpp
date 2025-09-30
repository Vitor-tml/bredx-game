#include "Ente.h"
#include <iostream>

// Iniciando variáveis estáticas e gerenciadores
int Ente::cont = 0;
Gerenciador::Renderer*        Ente::gGrafico  = Gerenciador::Renderer::getInstance();
Gerenciador::ResourceManager* Ente::gRecursos = Gerenciador::ResourceManager::getInstance();

Ente::Ente():
    id(++cont)
{
    // std::cout << "Construtora sem parametro (ente): " << id << " Adicionando placeHolder na sprite" << std::endl;
    sf::Texture placeHolder;
    placeHolder.create(64, 64);
    sprite.setTexture(placeHolder);
}
Ente::Ente(sf::Texture& figura):
    id(++cont)
{
    // std::cout << "Construtora com parametro(ente):  " << id << std::endl;

    sprite.setTexture(figura);
}
Ente::~Ente()
{
    // gGrafico = nullptr; ///< Não fazer isso porque a variável é compartilhada entre TODOS os entes.
}

void Ente::renderizar(int camada)
{
    // O objeto deve apenas se inserir na fila de renderização, a renderização final fica por parte da cena
    gGrafico->addDrawable(sprite, camada);
}

sf::Sprite Ente::getSprite() const
{ 
    return sprite;
}

void Ente::setTexture(sf::Texture& textura)
{
    sprite.setTexture(textura);
}

void Ente::setSize(const sf::Vector2f& size) {
    sf::Vector2f currentSize(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
    sf::Vector2f scale(size.x / currentSize.x, size.y / currentSize.y);
    sprite.setScale(scale);
}

sf::Vector2f Ente::getOrigin() const
{
    return sprite.getOrigin();
}