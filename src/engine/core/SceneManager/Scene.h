#ifndef _CENA_H
#define _CENA_H

#include <SFML/Graphics.hpp>
#include "engine/core/ResourceManager/ResourceManager.h"
#include "engine/graphics/Renderer/Renderer.h"

class Scene
{
public:
    Gerenciador::Renderer *janela;           ///< Ponteiro para o renderizador (Renderer)
    Gerenciador::ResourceManager *gRecursos; ///< Instância do gerenciador de recursos
    sf::Clock tempo;
    float deltaTime;

public:
    Scene() : janela(Gerenciador::Renderer::getInstance()),
              gRecursos(Gerenciador::ResourceManager::getInstance()) {};
    virtual ~Scene() {};
    virtual void inicializar() = 0;
    virtual void finalizar() = 0;
    virtual void executar() = 0;
    virtual void renderizar() = 0;
    virtual void processarEventos(const sf::Event &evento) = 0;
    virtual void pausar() {};  // Verificar necessidade de uma cena específica
    virtual void retomar() {}; // Verificar estado aqui
};
#endif