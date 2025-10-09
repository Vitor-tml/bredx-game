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
            // Se janela fechada encerra, senão trata evento
            if(evento.type == sf::Event::Closed)
                janela->close();
            else
                gCenas->processarEventosCenaAtual(evento);
        }
        // Aqui a lógica do jogo roda
        gCenas->atualizarCenaAtual();
        // Aqui a parte do gráfico do jogo roda
        gCenas->renderizarCenaAtual();
        // A renderização já usa um sistema de "fila" para renderizar, tudo que é gráfico se centraliza
        // no mesmo renderizador, será que faz sentido ter algo que delega o atualizar também
    }
}