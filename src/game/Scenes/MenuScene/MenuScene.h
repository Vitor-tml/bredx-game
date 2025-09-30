#ifndef _MENUSCENE_H
#define _MENUSCENE_H

#include "engine/graphics/Renderer/Renderer.h"
#include "engine/core/ResourceManager/ResourceManager.h"
#include "MenuScene.h"
#include "game/Scenes/GameScene/GameScene.h"
#include "game/Scenes/CreditsScene/CreditsScene.h"
#include "engine/core/SceneManager/SceneManager.h"
#include <iostream>

class MenuScene : public Scene {
private:
    sf::Sprite background;
    sf::Sprite button[2];
    sf::Sprite select[2];
    sf::Music *music;
    int selectedButton; // Variável para controlar qual botão está selecionado
    void selecionarBotao(int index); // Método para selecionar um botão

public:
    MenuScene();
    ~MenuScene();
    void inicializar() override;
    void executar() override;
    void renderizar() override;
    void processarEventos(const sf::Event &evento) override;
    void finalizar() override;
};
#endif