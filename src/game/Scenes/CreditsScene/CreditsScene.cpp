#include "CreditsScene.h"
#include <iostream>
#include <cmath>

CreditsScene::CreditsScene() : elapsedTime(0) {}

CreditsScene::~CreditsScene() {}

void CreditsScene::inicializar() {

    gRecursos->loadMusic("creditos", "../assets/musics/creditos.wav");
    music = gRecursos->getMusic("creditos");
    music->setLoop(true);
    music->setVolume(50);
    music->play();
    janela->setIsShader(true);
    janela->setCentroCamera(janela->getTamanho().x/2,janela->getTamanho().y/2);
    janela->setTamanhoCamera(janela->getTamanho().x,janela->getTamanho().y);
    if (!font.loadFromFile("../assets/fonts/fonte.ttf")) { // Substitua pelo caminho do seu arquivo de fonte
        std::cout << "Erro ao carregar fonte" << std::endl;
    }

    creditsText.setFont(font);
    creditsText.setString("Creditos:\n\nDesenvolvedor: Vitor Silva (@vitor.tml)\n\nGraficos: Brenda Alves (@brealvsz)\n\nMusica: Joao Manfron(@joao.manfron)");
    creditsText.setCharacterSize(24);
    creditsText.setFillColor(sf::Color::White);
    
    // Ajuste a posição inicial do texto para que ele fique centralizado
    sf::FloatRect textBounds = creditsText.getLocalBounds();
    creditsText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f); // Define o centro como origem
    creditsText.setPosition(400, 500); // Centraliza o texto na tela (ajuste conforme necessário)

    background.setSize(sf::Vector2f(800, 600)); // Ajuste o tamanho conforme necessário
    background.setFillColor(sf::Color::Black);
}

void CreditsScene::executar() {
    float deltaTime = clock.restart().asSeconds();

    elapsedTime += deltaTime;
    // Movimento vertical suave do texto
    float amplitude = 30.0f; // Amplitude do movimento
    float speed = 1.0f; // Velocidade do movimento
    float yOffset = amplitude * sin(speed * elapsedTime); // Calcula o deslocamento vertical usando uma função seno

    creditsText.setPosition(400, 350 + yOffset); // Atualiza a posição do texto

    // Opcional: Reinicia a animação se necessário
    if (elapsedTime > 2 * M_PI / speed) {
        elapsedTime = 0;
    }
}

void CreditsScene::renderizar() {
    janela->addDrawable(background, 0);
    janela->addDrawable(creditsText, 1);
    janela->render();
}

void CreditsScene::processarEventos(const sf::Event &evento) {
    
}

void CreditsScene::finalizar() {
    music->stop();
    // Limpeza necessária, se houver
}
