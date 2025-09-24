#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include <iostream>
#include "../../../engine/CollisionManager/CollisionManager.h"
#include "../../../engine/TileMap/TileMap.h"
#include "../../../engine/SceneManager/Scene.h"
#include "../../../engine/SceneManager/SceneManager.h"
#include "../../../engine/Paralaxe/Paralaxe.h"
#include "../MenuScene/MenuScene.h"
#include "../../Entity/Entity.h" 

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