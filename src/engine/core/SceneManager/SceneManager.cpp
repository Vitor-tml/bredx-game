#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::singleton = nullptr;

SceneManager::SceneManager() : fadeOpacity(0.0f), fadingIn(false), fadingOut(false) {
    fadeShape.setSize(sf::Vector2f(10000, 10000)); // Ajuste conforme necessário para o tamanho da tela
    fadeShape.setFillColor(sf::Color(0, 0, 0, 0));
    fadeShape.setPosition(sf::Vector2f(-1000, -1000));
}

SceneManager::~SceneManager() {}

SceneManager* SceneManager::getInstance() {
    if (!singleton) {
        singleton = new SceneManager();
    }
    return singleton;
}

void SceneManager::startFadeIn() {
    fadingIn = true;
    fadeOpacity = 255.0f;
    fadeShape.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeOpacity)));
}

void SceneManager::startFadeOut(std::unique_ptr<Scene> novaCena) {
    fadingOut = true;
    fadeOpacity = 0.0f;
    fadeShape.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeOpacity)));
    nextScene = std::move(novaCena);
}

void SceneManager::mudarCena(std::unique_ptr<Scene> novaCena) {
    startFadeOut(std::move(novaCena));
}

void SceneManager::empilharCena(std::unique_ptr<Scene> novaCena) {
    if (!cenas.empty()) {
        cenas.top()->finalizar();
    }
    cenas.push(std::move(novaCena));
    cenas.top()->inicializar();
}

void SceneManager::desempilharCena() {
    if (!cenas.empty()) {
        cenas.top()->finalizar();
        cenas.pop();
    }
    if (!cenas.empty()) {
        cenas.top()->inicializar();
    }
}

void SceneManager::atualizarCenaAtual() {
    if (fadingIn) {
        fadeOpacity -= 5.0f; // Ajuste a velocidade do fade conforme necessário
        if (fadeOpacity <= 0.0f) {
            fadeOpacity = 0.0f;
            fadingIn = false;
        }
        fadeShape.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeOpacity)));
    } else if (fadingOut) {
        fadeOpacity += 5.0f;
        if (fadeOpacity >= 255.0f) {
            fadeOpacity = 255.0f;
            fadingOut = false;
            if (!cenas.empty()) {
                cenas.top()->finalizar();
                cenas.pop();
            }
            cenas.push(std::move(nextScene));
            cenas.top()->inicializar();
            startFadeIn();
        }
        fadeShape.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeOpacity)));
    }

    if (!cenas.empty()) {
        cenas.top()->executar();
    }
}

void SceneManager::renderizarCenaAtual() {
    if (!cenas.empty()) {
        cenas.top()->renderizar();
    }
    if (fadingIn || fadingOut) {
        // Renderize o fadeShape por cima de tudo
        Gerenciador::Renderer::getInstance()->addDrawable(fadeShape, 10);
    }
}

void SceneManager::processarEventosCenaAtual(const sf::Event& evento) {
    if (!cenas.empty() && !fadingOut) {
        cenas.top()->processarEventos(evento);
    }
}
