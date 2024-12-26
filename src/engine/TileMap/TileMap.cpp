#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "json.hpp"

using namespace nlohmann;

/**
 * @brief Componente responsável pelo carregamento do mapa no jogo
 */
namespace TileEngine{
// Tilemap
TileMap::TileMap(){}
TileMap::~TileMap(){}

void TileMap::loadMapFromFile(const std::string& filename)
{
    std::fstream arquivo(filename);

    if(!arquivo.is_open()){
        std::cout << "ERRO::TILEMAP::LOADMAPFROMFILE::Arquivo nao pode ser aberto: " << filename << std::endl;
        return;
    }

    json j;
    arquivo >> j;
    
    arquivo.close();

    tileSize = j["tilewidth"];
    height = j["height"];
    width = j["width"];

    // Matriz linearizada
    std::vector<int> vetorTiles = j["layers"][0]["data"].get<std::vector<int>>();
    // Matriz quadrada
    matrizTiles.resize(height, std::vector<int>(width));
    matrizEntidades.resize(height, std::vector<TileEntity*>(width));
    coordenadas.resize(height, std::vector<sf::Vector2f>(width));
    // Convertendo matriz linear para quadrada
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrizTiles[i][j] =  vetorTiles[i * width + j];
            coordenadas[i][j] = sf::Vector2f(j * tileSize, i * tileSize);
            if(matrizTiles[i][j]){
                bool tipo = (matrizTiles[i][j] == 3 || matrizTiles[i][j] == 4)? 1 : 0; // Mudar depois para algo mais dinâmico
                TileEntity* novoTile = new TileEntity(sheet, j, i, matrizTiles[i][j] - 1, 0, tileSize, tipo);
                matrizEntidades[i][j] = novoTile;
                lTiles.push_back(novoTile);
            }else{
                matrizEntidades[i][j] = nullptr;
            }
        }
    }
}
std::vector<Entity*> TileMap::getEntitys()
{
    std::vector<Entity*> tiles;
    for(TileEntity *t : lTiles)
        tiles.push_back(t);
    return tiles;
}
void TileMap::loadSheet(sf::Texture& textura)
{
    sheet = textura;
}

// Tile entity
TileEntity::TileEntity(sf::Texture &textura, int x, int y, int xTile, int yTile, int tileSize, bool colide)
           :Entity(textura, x * tileSize, y * tileSize, colide)
{
    sprite.setTextureRect(sf::IntRect(xTile * tileSize, yTile * tileSize, tileSize, tileSize));
    criarHitBox();
    atualizaHitBox();
}

sf::Vector2f TileMap::getOrigem() const
{
    return sf::Vector2f( 0 * tileSize, height * tileSize);
}
void TileMap::atualizarMapa(sf::View& camera)
{
    atualizarCoordenadas(camera);
    atualizarTiles();
}

void TileMap::atualizarCoordenadas(sf::View& view)
{
    // Obter as coordenadas da view atual
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    sf::FloatRect viewRect(
        viewCenter.x - viewSize.x / 2.f, // left
        viewCenter.y - viewSize.y / 2.f, // top
        viewSize.x, // width
        viewSize.y  // height
    );

    sf::FloatRect mapRect(
        coordenadas[0][0].x,
        coordenadas[0][0].y,
        tileSize * width,
        tileSize * height
    );

    if (viewRect.left < mapRect.left) {
        moverColunas(-1);
    }

    if (viewRect.left + viewRect.width > mapRect.left + mapRect.width) {
        moverColunas(1);
    }
}

void TileMap::moverColunas(int direcao)
{
    std::vector<sf::Vector2f> coordenadasNovas;
    std::vector<TileEntity*> tempTile;
    coordenadasNovas.resize(height);
    tempTile.resize(height);

    if(direcao == -1)
    {
        // Atualiza coordenadas da ultima coluna
        for (int k = 0; k < height; k++)
        {
            coordenadas[k][width - 1] = coordenadas[k][0] - sf::Vector2f(tileSize, 0);
            coordenadasNovas[k] = coordenadas[k][width - 1];
            tempTile[k] = matrizEntidades[k][width - 1];
        }
        // Coloca todas as colunas uma posicao pra frente
        for(int i = height - 1; i >= 0;  i--) {
            for(int j = width - 1; j >= 0; j--){
                coordenadas[i][j] = coordenadas[i][j - 1];
                matrizEntidades[i][j] = matrizEntidades[i][j -  1];
            }
        }
        // Coloca a coluna modificada no início
        for(int i = 0; i < height; i++)
        {
            coordenadas[i][0] = coordenadasNovas[i];
            matrizEntidades[i][0] = tempTile[i];
        }
    }
    else
    {
        // Atualiza coordenadas da primeira coluna
        for(int k = 0; k < height; k++)
        {
            coordenadas[k][0] = coordenadas[k][width - 1] + sf::Vector2f(tileSize, 0);
            coordenadasNovas[k] = coordenadas[k][0];
            tempTile[k] = matrizEntidades[k][0];
        }
        // Coloca todas as colunas uma posicao pra tras
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++){
                coordenadas[i][j] = coordenadas[i][j + 1];
                matrizEntidades[i][j] = matrizEntidades[i][j + 1];
            }
        }
        // Colocar a coluna modificada no início
        for(int i = 0;  i < height; i++)
        {
            coordenadas[i][width - 1] = coordenadasNovas[i];
            matrizEntidades[i][width - 1] = tempTile[i];
        }
    }
}

void TileMap::atualizarTiles()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(matrizEntidades[i][j]  != nullptr) {
            matrizEntidades[i][j]->setPosicao(coordenadas[i][j]);
            }
        }
    }
}
}