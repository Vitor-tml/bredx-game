#include "GameScene.h"

GameScene::GameScene()
{
    gNiveis = Gerenciador::LevelManager::getInstance();
}

GameScene::~GameScene()
{
    delete player;
}

void GameScene::inicializar()
{
    gNiveis->inicializar();
 
    sf::Image playerImage;
    playerImage.create(16, 16, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    
    // Arrumar essas gambiarras depois =============================================================
    player = new Player(gRecursos->getTexture("jogador"), 0, 0, 10, 2, 10);
    player->setPosicao(0, 0);
    lEntidades.push_back(player);
    
    for(Entity* entidade : lEntidades){
        if(entidade->getColisao())
            gColisao.addEntity(entidade);
    }

    janela->setMoveBounds(sf::FloatRect(200, 200, 100, 300)); // Exemplo de retângulo de 200x200

}

void GameScene::executar()
{
    deltaTime = tempo.restart().asSeconds();
    
    sf::View cameraDev;
    cenario.atualizar(janela->getView());

    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }
    gColisao.tratarColisoes();
    for(Entity* e : lEntidades)
    {
        e->executar(deltaTime);
    }
    janela->updateCamera(player->getPosicao());
    map.atualizarMapa(janela->getView());
}

void GameScene::renderizar()
{
    cenario.renderizar();

    for(Entity* e : lEntidades)
    {
        e->renderizar(5);
        // janela->addDrawable(e->getHitBox(), 3);
    }
    // std::cout << player->getPosicao().y << std::endl;
    // janela->setCentroCamera(player->getPosicao().x, player->getPosicao().y);

    janela->render();
}

void GameScene::processarEventos(const sf::Event &evento)
{
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        // Voltar para o menu ou outra cena quando a tecla Escape for pressionada
        SceneManager::getInstance()->mudarCena(std::make_unique<MenuScene>());
    }
}

void GameScene::finalizar()
{
    if (musica)
    {
        float volume = musica->getVolume();
        float step = volume / 50.0f;  // Ajuste o divisor para controlar a duração do fade-out

        while (volume > 0)
        {
            volume -= step;
            musica->setVolume(volume);
            sf::sleep(sf::milliseconds(20));  // Ajuste o tempo para controlar a suavidade do fade-out
        }

        musica->stop();
    }
}