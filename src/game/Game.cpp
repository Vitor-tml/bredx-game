#include "Game.h"
#include <iostream>

Game::Game():
    janela(Gerenciador::Renderer::getInstance()),
    gCenas(SceneManager::getInstance())
{
    // janela->carregarShaders();
    // janela->setIsShader(true);
}

Game::~Game()
{
    
}

void Game::executar()
{
    gCenas->empilharCena(std::make_unique<MenuScene>());
    // gCenas->empilharCena(std::make_unique<GameScene>());

    while(janela->isOpen())
    {
        sf::Event evento;
        while(janela->pollEvent(evento)) // Importante pegar os eventos antes de tratar!
        {
        if(evento.type == sf::Event::Closed)
            janela->close();
        else
            gCenas->processarEventosCenaAtual(evento);
        }
        gCenas->atualizarCenaAtual();
        gCenas->renderizarCenaAtual();
    }
}

