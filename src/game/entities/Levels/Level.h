#pragma once

#include "engine/world/TileMap/TileMap.h"
#include <vector>
#include "unordered_map"
class Level {
private:
    TileEngine::TileMap map;                ///< Instância do mapa de tiles
    std::vector<Entity*> lEntidades;
    std::unordered_map<sf::Music*, std::string> musicas;
public:
    Level();
    ~Level();

    void carregarTexturas();
    void carregarMusicas();
    void carregarMapa(const std::string& filename);
    void carregarEntidades();
};