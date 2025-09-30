#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include <iostream>
#include "engine/physics/CollisionManager/CollisionManager.h"
#include "engine/world/TileMap/TileMap.h"
#include "engine/core/SceneManager/Scene.h"
#include "engine/core/SceneManager/SceneManager.h"
#include "engine/graphics/Paralaxe/Paralaxe.h"
#include "game/Scenes/MenuScene/MenuScene.h"
#include "game/entities/Entity/Entity.h"

class GameScene : public Scene {
private:
    Gerenciador::CollisionManager gColisao; ///< Instância do gerenciador de colisões
    TileEngine::TileMap map;                ///< Instância do mapa de tiles
    Parallax cenario;
    Player* player;
    std::vector<Entity*> lEntidades;
    sf::Music *musica;
public:
    GameScene();
    ~GameScene();
    void inicializar();
    void executar();
    void renderizar();
    void finalizar();
    void processarEventos(const sf::Event &evento);
};
#endif