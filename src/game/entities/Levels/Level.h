#pragma once

#include "engine/world/TileMap/TileMap.h"
#include "engine/core/ResourceManager/ResourceManager.h"
#include "engine/graphics/Paralaxe/Paralaxe.h"
#include <vector>
#include "unordered_map"
class Level {
private:
    TileEngine::TileMap map;                ///< Instância do mapa de tiles
    Parallax cenario;
    std::vector<Entity*> lEntidades;
    std::unordered_map<std::string, sf::Music*> musicas;
    Gerenciador::ResourceManager* gRecursos;
public:
    Level();
    ~Level();

    void carregarTexturas();
    void carregarMusicas();
    void carregarMapa();
    void carregarEntidades();
    void carregarCenario();
    const std::vector<Entity*>& getEntidades();
};