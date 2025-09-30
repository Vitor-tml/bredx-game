#ifndef _GERENCIADOR_DE_CENAS_H
#define _GERENCIADOR_DE_CENAS_H

#include <stack>
#include <memory>
#include "Scene.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Classe SceneManager é responsável por gerenciar as cenas do jogo.
 * Utiliza o padrão Singleton para garantir que apenas uma instância do gerenciador de cenas exista.
 * As cenas são armazenadas em uma pilha, permitindo empilhar, desempilhar e trocar de cenas.
 */
class SceneManager {
private:
    static SceneManager *singleton; ///< Ponteiro para a instância singleton
    SceneManager();               ///< Construtora privada para implementação do singleton
    std::stack<std::unique_ptr<Scene>> cenas; ///< Pilha para armazenar as cenas

    sf::RectangleShape fadeShape;
    float fadeOpacity;
    bool fadingIn;
    bool fadingOut;
    std::unique_ptr<Scene> nextScene;

    void startFadeIn();
    void startFadeOut(std::unique_ptr<Scene> novaCena);

public:
    void operator=(const SceneManager&) = delete; ///< Evitando atribuições do objeto
    SceneManager(const SceneManager&) = delete;   ///< Evitando cópias do objeto
    ~SceneManager();

    static SceneManager* getInstance();

    void mudarCena(std::unique_ptr<Scene> novaCena);
    void empilharCena(std::unique_ptr<Scene> novaCena);
    void desempilharCena();

    void atualizarCenaAtual();
    void renderizarCenaAtual();
    void processarEventosCenaAtual(const sf::Event& evento);
};

#endif
