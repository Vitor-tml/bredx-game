#ifndef _PARALLAX_H
#define _PARALLAX_H

#include "engine/world/Ente/Ente.h"
#include <vector>
struct Camada
{
    sf::Sprite sprite[2];
    float velocidade;
    float camada;
};

class Parallax : public Ente{
private:
    std::vector<Camada*> layers;
    sf::Vector2f lastCameraPosition;
    float multiplicadorParalax;
public:
    Parallax();
    ~Parallax();
    void addLayer(sf::Texture& textura, float speed, int camada = 0);
    void atualizar(sf::View& camera);
    void renderizar();
    void setPosition(sf::Vector2f origem);
    void estenderLayer(sf::View& camera);
};

#endif // _PARALLAX_H