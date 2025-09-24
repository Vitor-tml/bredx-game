#pragma once

#include "../../../engine/SceneManager/Scene.h"
#include "../../../engine/SceneManager/SceneManager.h"

class DebugScene : public Scene {
    Gerenciador::SceneManager sceneManager; ///< Instância do gerenciador de cenas
    Player* player;
    std::vector<Entity*> lEntidades;
public:
    DebugScene();
    ~DebugScene();
    void inicializar();
    void executar();
    void renderizar();
    void finalizar();
    void processarEventos(const sf::Event &evento);
};