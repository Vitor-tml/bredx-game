#ifndef _ENTE_H
#define _ENTE_H

#include <SFML/Graphics.hpp>
#include "engine/graphics/Renderer/Renderer.h"
#include "engine/core/ResourceManager/ResourceManager.h"
/**
 * @class Ente
 * @brief Classe base para todos os elementos visuais do jogo.
 * 
 * A classe Ente é responsável por representar elementos visuais
 * no jogo e fornecer funcionalidades básicas como renderização.
 * @author Vitor-tml
 */
class Ente{
protected:
    const int id;                                   //< Indentificador para permanência de objeto
    static int cont;                                //< Contador de ID
    static Gerenciador::Renderer*        gGrafico;  //< Instância única do renderer
    static Gerenciador::ResourceManager* gRecursos; //< Instancia única do gerenciador de recursos
    sf::Sprite sprite;                              //< Shape a ser desenhado do elemento.
public:
    /**
     * @brief Construtora da classe-base Ente.
     * 
     * Inicia o atríbuto id e inicia "figura" com um place holder.
     */
    Ente();
    
    /**
     * @brief Construtora com parâmetros da classe base Ente
     * 
     * Inicia o atríbuto id define a textura do sprite
     */
    Ente(sf::Texture& figura);
    
    /**
     * @brief Destrutora da classe-base Ente.
     * 
     * Apenas para criar explicitamente o método.
     */
    virtual ~Ente();
    
    /**
     * @brief Método que renderiza o objeto na tela.
     * 
     * Adiciona a sprite do objeto na fila de renderização do gerenciador gráfico.
     * @param camada ordem de renderização na tela, quando maior mais pra frente.
     */
    void renderizar(int camada = 0);
    
    /**
     * @brief Retorna o sprite do Ente
     * @return sf::Sprite 
     */
    sf::Sprite getSprite() const;
    
    /**
     * @brief Nova textura do Ente
     * @param textura nova textura do ente
     */
    void setTexture(sf::Texture& textura);

    /**
     * @brief Muda o tamanho da sprite do ente baseado na escala
     * @param size sf::Vector2f(aumento verticall, aumento horizontal)
     */
    void setSize(const sf::Vector2f& size);

    /**
     * @brief Retorna a origem da sprite, o ponto por onde coordenada é orientada
     * @return sf::Vector2f 
     */
    sf::Vector2f getOrigin() const;

    int  getId() const {return id;};
};
#endif