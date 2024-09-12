#include "engine/Renderer/Renderer.h"
#include "game/Entity/Entity.h"
#include "engine/TileMap/Tilemap.h"

int main()
{

    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(800, 600, "Prodislexos Game");


    // Define os tiles do mapa (0, 1, 2, ...)
    std::vector<int> level = {
        1, 2,
        2, 1
    };

    // Cria um Tilemap
    Tilemap map;
    if (!map.load("../assets/textures/tileset.png", sf::Vector2u(16, 16), level, 2, 2)) {
        return -1;
    }




    sf::Image playerImage;
    playerImage.create(50, 50, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    Entity player(playerTextura, 400, 300);
    sf::Clock clock;    
    float deltaTime;
    while(janela->isOpen())
    {
        sf::Event evento;
        while(janela->pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                janela->close();
        }
        deltaTime = clock.restart().asSeconds();
        player.executar(deltaTime);
        player.renderizar();
        janela->addDrawable(map);
        janela->render();
    }
}