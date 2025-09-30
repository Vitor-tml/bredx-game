#include "MenuScene.h"
MenuScene::MenuScene() : selectedButton(0) {}

MenuScene::~MenuScene() {}

void MenuScene::inicializar() {

    janela->tirarShader();
    std::cout << "Inicializando MenuScene" << std::endl;
    janela->setCentroCamera(janela->getTamanho().x/2,janela->getTamanho().y/2);
    janela->setTamanhoCamera(janela->getTamanho().x,janela->getTamanho().y);
    gRecursos->loadTexture("menu", "../assets/textures/menu.png");
    gRecursos->loadTexture("butao", "../assets/textures/butao.png");
    gRecursos->loadTexture("select", "../assets/textures/selecionado.png");
    gRecursos->loadMusic("menu", "../assets/musics/menu.wav");

    background.setTexture(gRecursos->getTexture("menu"));
    background.setPosition(0, 0);

    for (int i = 0; i < 2; i++) {
        button[i].setTexture(gRecursos->getTexture("butao"));
        button[i].setPosition(495, i * 53 + 10 + 364);
        button[i].setTextureRect(sf::IntRect(0, i * 43, 290, 43));

        select[i].setTexture(gRecursos->getTexture("select"));
        select[i].setPosition(495, i * 53 + 10 + 364);
        select[i].setTextureRect(sf::IntRect(0, i * 43, 290, 43));
    }

    music = gRecursos->getMusic("menu");
    music->setVolume(0); // Começar com volume zero
    music->setLoop(true);
    music->play();

    // Fade-in effect
    float targetVolume = 50; // Volume final desejado
    float currentVolume = 0;
    float step = targetVolume / 50.0f;  // Ajuste o divisor para controlar a duração do fade-in

    while (currentVolume < targetVolume) {
        currentVolume += step;
        music->setVolume(currentVolume);
        sf::sleep(sf::milliseconds(20));  // Ajuste o tempo para controlar a suavidade do fade-in
    }

    selecionarBotao(0);
}

void MenuScene::executar() {
    // Lógica adicional, se necessário
}

void MenuScene::renderizar() {
    janela->addDrawable(background, 0);
    for (int i = 0; i < 2; i++) {
        if(i == selectedButton)
            janela->addDrawable(select[i], 1);
        else
            janela->addDrawable(button[i], 1);
    }
    janela->render();
}

void MenuScene::processarEventos(const sf::Event &evento) {
    std::cout << "Processando eventos" << std::endl;
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Up) {
            selecionarBotao((selectedButton - 1 + 2) % 2); // Corrigido: Mover para cima
        } else if (evento.key.code == sf::Keyboard::Down) {
            selecionarBotao((selectedButton + 1) % 2); // Corrigido: Mover para baixo
        } else if (evento.key.code == sf::Keyboard::Enter) {
            if (selectedButton == 0) {
                // Trocar para a cena do jogo
                std::cout << "Entrando no game" << std::endl;
                SceneManager::getInstance()->mudarCena(std::make_unique<GameScene>());
            } else if (selectedButton == 1) {
                std::cout << "Entrando nos créditos" << std::endl;
                // Trocar para a cena de créditos
                SceneManager::getInstance()->mudarCena(std::make_unique<CreditsScene>());
            }
        }
    }
}

void MenuScene::finalizar() {
    if (music)
    {
        float volume = music->getVolume();
        float step = volume / 50.0f;  // Ajuste o divisor para controlar a duração do fade-out

        while (volume > 0)
        {
            volume -= step;
            music->setVolume(volume);
            sf::sleep(sf::milliseconds(20));  // Ajuste o tempo para controlar a suavidade do fade-out
        }

        music->stop();
    }
}

void MenuScene::selecionarBotao(int index) {
    selectedButton = index;
}
