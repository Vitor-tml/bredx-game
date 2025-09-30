#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H

#include "engine/core/SceneManager/Scene.h"
#include "engine/core/SceneManager/SceneManager.h"
#include "game/Scenes/MenuScene/MenuScene.h"
#include <SFML/Graphics.hpp>
#include <string>

class CreditsScene : public Scene {
public:
    CreditsScene();
    ~CreditsScene();

    void inicializar() override;
    void executar() override;
    void renderizar() override;
    void processarEventos(const sf::Event &evento) override;
    void finalizar() override;

private:
    sf::Text creditsText;
    sf::Font font;
    sf::RectangleShape background;
    sf::Clock clock;
    sf::Music *music;
    float elapsedTime;
};

#endif // CREDITS_SCENE_H
