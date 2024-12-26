#ifndef _TILEMAP_H
#define _TILEMAP_H

#include <string>
#include <vector>
#include "../../game/Entity/Entity.h"
namespace TileEngine {

class TileEntity : public Entity {
private:
    int id;
public:
    TileEntity(sf::Texture &textura, int x, int y, int xTile, int yTile, int tileSize, bool colide = 0);
    ~TileEntity(){};
    void executar(float deltaTime) override { atualizaHitBox();};
    void colidiuComTile(Entity* e) override {};
    void colidiu(Entity* e) override { e->colidiuComTile(this); };
};
class TileMap {
private:
    int tileSize;
    int height;
    int width;
    std::vector<std::vector<int>> matrizTiles;
    std::vector<std::vector<TileEntity*>> matrizEntidades;
    std::vector<std::vector<sf::Vector2f>> coordenadas;
    std::vector<TileEntity*> lTiles;
    sf::Texture sheet;
public:
    TileMap();
    ~TileMap();
    void loadMapFromFile(const std::string& filename);
    void loadSheet(sf::Texture& textura);
    std::vector<Entity*> getEntitys();
    sf::Vector2f getOrigem() const;
    void atualizarCoordenadas(sf::View& view);
    void atualizarTiles();
    void atualizarMapa(sf::View& camera);
    void moverColunas(int direcao);
};
}
#endif