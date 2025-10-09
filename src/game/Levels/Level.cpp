#include "Level.h"

Level::Level()
: gRecursos(Gerenciador::ResourceManager::getInstance())
{

}

Level::~Level(){}

void Level::carregarTexturas()
{
    gRecursos->loadTexture("jogador", "../assets/textures/protagonista.png");
    gRecursos->loadTexture("cenario1", "../assets/textures/cenario1.png");    
    gRecursos->loadTexture("cenario2", "../assets/textures/cenario2.png");
    gRecursos->loadTexture("cenario3", "../assets/textures/cenario3.png");
    gRecursos->loadTexture("tilesheet", "../assets/newmap/sheets.png");
    gRecursos->loadTexture("animacao", "../assets/textures/protagonistaSheet.png");
}

void Level::carregarMusicas()
{
    gRecursos->loadMusic("game", "../assets/musics/jogo.wav");

    sf::Music *musica;
    musica = gRecursos->getMusic("game");
    musica->play();
    musica->setLoop(true);
    musica->setVolume(30); // Ajuste o volume conforme necessário

    // Testar se está passando o conteúdo ou o endereço
    musicas["main"] = musica;
}

void Level::carregarMapa()
{
    map.loadMapFromFile("../assets/newmap/mapa.tmj");
    map.loadSheet(gRecursos->getTexture("tilesheet"));

}

void Level::carregarCenario()
{
    cenario.addLayer(gRecursos->getTexture("cenario3"), 0.1,  0);
    cenario.addLayer(gRecursos->getTexture("cenario2"), 0.2, 1);
    cenario.addLayer(gRecursos->getTexture("cenario1"), 0,    2);

    cenario.setPosition(map.getOrigem() + sf::Vector2f(0, 50));
}

void Level::carregarEntidades()
{
    // Entidades do mapa(chão)
    std::vector<Entity*> lTiles = map.getEntitys();
    for(Entity* e :  lTiles) {
        lEntidades.push_back(e);
    }
}

// Constante para nao mexer na lista e referencia para poder usar como obj puro
const std::vector<Entity*>& Level::getEntidades()
{
    return lEntidades;
}

