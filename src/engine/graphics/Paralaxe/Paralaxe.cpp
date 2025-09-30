#include "Paralaxe.h"
#include <iostream>

Parallax::Parallax()
{
    multiplicadorParalax = 1.5;
}
Parallax::~Parallax(){}

void Parallax::addLayer(sf::Texture& textura, float velocidade, int camada)
{
    Camada* novaCamada = new Camada;
    novaCamada->sprite[0].setTexture(textura);
    novaCamada->sprite[0].setOrigin(0, novaCamada->sprite[0].getGlobalBounds().height);
    novaCamada->velocidade = velocidade;
    novaCamada->sprite[1].setTexture(textura);
    novaCamada->sprite[1].setOrigin(0,  novaCamada->sprite[1].getGlobalBounds().height);
    novaCamada->sprite[1].setPosition(novaCamada->sprite[0].getGlobalBounds().width, 0); // Posiciona logo após o fim da camada
    novaCamada->camada = camada;
    layers.push_back(novaCamada);

}

void Parallax::setPosition(sf::Vector2f origem)
{
    for(Camada* s : layers){
        s->sprite[0].setPosition(origem);
        s->sprite[1].setPosition(origem + sf::Vector2f(s->sprite[0].getGlobalBounds().width, 0));
    }
}

void Parallax::atualizar(sf::View& camera)
{
    sf::Vector2f coordCam = camera.getCenter();
    sf::Vector2f delta = coordCam - lastCameraPosition; // Calcula a mudança na posição da câmera

    for (Camada* layer : layers) {
        // Atualiza a posição da camada com base na mudança da câmera
        sf::Vector2f antigaCoord = layer->sprite[0].getPosition();
        layer->sprite[0].setPosition(antigaCoord.x + delta.x * layer->velocidade, antigaCoord.y);
        antigaCoord = layer->sprite[1].getPosition();
        layer->sprite[1].setPosition(antigaCoord.x + delta.x * layer->velocidade, antigaCoord.y);
    }

    // Atualiza a última posição da câmera
    lastCameraPosition = coordCam;

    estenderLayer(camera);
}

void Parallax::renderizar()
{
    for (int i = 0; i < layers.size(); i++){
        gGrafico->addDrawable(layers[i]->sprite[0], layers[i]->camada);
        gGrafico->addDrawable(layers[i]->sprite[1], layers[i]->camada);
    }
}

void Parallax::estenderLayer(sf::View& camera)
{
    // Obter as coordenadas da view atual
    sf::Vector2f viewCenter = camera.getCenter();
    sf::Vector2f viewSize = camera.getSize();

    sf::FloatRect rectCam(
        viewCenter.x - viewSize.x / 2.f, // left
        viewCenter.y - viewSize.y / 2.f, // top
        viewSize.x, // width
        viewSize.y  // height
    );

    for(Camada* l : layers)
    {
        int esquerda = (l->sprite[0].getGlobalBounds().left < l->sprite[1].getGlobalBounds().left)? 0 : 1;
        int direita = !esquerda;
        sf::FloatRect rectLayer(
            l->sprite[esquerda].getGlobalBounds().left,
            l->sprite[esquerda].getGlobalBounds().top,
            l->sprite[esquerda].getGlobalBounds().width  * 2,
            l->sprite[esquerda].getGlobalBounds().height * 2
        );

        if(rectCam.left < rectLayer.left)
        {
            l->sprite[direita].setPosition(l->sprite[esquerda].getPosition().x - l->sprite[esquerda].getGlobalBounds().width, l->sprite[esquerda].getPosition().y);
        }
        
        if(rectCam.left + rectCam.width > rectLayer.left + rectLayer.width)
        {
            l->sprite[esquerda].setPosition(l->sprite[direita].getPosition().x + l->sprite[direita].getGlobalBounds().width, l->sprite[direita].getPosition().y);
        }
    }
}