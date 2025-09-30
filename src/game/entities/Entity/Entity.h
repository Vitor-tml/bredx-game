#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "engine/world/Ente/Ente.h"
#include "engine/physics/PhysicsComponent/PhysicsComponent.h"


/**
 * @class Entity
 * @brief Classe base para entidades no jogo.
 * 
 * Esta é uma classe abstrata que define a interface para todas as entidades no jogo.
 * As classes derivadas devem implementar os métodos puros virtuais `executar`.
 * @see Ente
 * @author Vitor-tml
 */
class Entity : public Ente {
protected:
    sf::Vector2f posicao;      //< Coordenada x e y do entidade na tela
    sf::Vector2f velocidade;   //< Velocidade vetorial  do entidade
    bool colisao;
    sf::RectangleShape hitBox; //< Hitbox da entidade
    PhysicsComponent fisica;   //< Componente responsável pela gravidade, aceleração, movimento, etc.
    sf::Vector2f hitBoxSize;   //< Tamanho da hitbox do entidade para hitbox configurada manualmente
    sf::Vector2f hitBoxOffset; //< Diferença entre o tamanho da sprite da entidade e sua hitBox
public:
    /**
     * @brief Construtor padrão da classe Entity.
     * Inicializa as coordenadas em (0, 0), configura a origem da entidade para o meio inferior da sprite e cria a hitbox com base na sprite.
     */
    Entity(int x = 0, int y = 0);

    /**
     * @brief Construtora com parâmetro de posição e textura.
     * Faz as mesmas configurações da construtora sem parâmetro mas adiciona sprite e posição.
     * @param x coordenada no eixo x 
     * @param y coordenada no eixo y
     * @param textura objeto textura do SFML
     */
    Entity(sf::Texture &textura,  int x = 0, int y = 0, bool colide = 1);

    /**
     * @brief Destruidor da classe Entity.
     * 
     * O destruidor é virtual para garantir a destruição correta das classes derivadas.
     */
    virtual ~Entity() {}

    /**
     * @brief Método para executar a lógica da entidade.
     * 
     * Este método deve ser implementado pelas classes derivadas para definir o comportamento específico da entidade.
     * @param deltaTime variação do tempo para aplicação das lógicas de gravidade, movimento, etc. 
     */
    virtual void executar(float deltaTime);

    /**
     * @brief Retorna a hitbox da entidade
     * @return sf::RectangleShape& 
     */
    sf::RectangleShape& getHitBox();

    /**
     * @brief Move o entidade até uma coordenada (x, y)
     * @param x posição no eixo x
     * @param y posição no eixo y
     */
    void setPosicao(int x, int y);
    /**
     * @brief Move a entidade até uma cordenada (x, y)
     * @param novaPosicao sf::Vector2f(float, float)
     */
    void setPosicao(sf::Vector2f novaPosicao);

    /**
     * @brief Retorna a coordenada da entidade em um vetor (x, y)
     * @return sf::Vector2f 
     */
    sf::Vector2f getPosicao() const;

    /**
     * @brief Configura a origem da sprite da entidade no meio da base da sprite
     */
    void setOrigin();

     /**
     * @brief Cria e atualiza a hitbox da entidade com base na sprite ou hitbox personalizada e posição da entidade
     */
    void criarHitBox();

    /**
     * @brief Define o tamanho personalizado da hitBox
     * @param size tamanho da hitbox
     */
    void setHitBoxSize(sf::Vector2f size);

    /**
     * @brief Define o offset(diferença) entre a sprite e a hitbox da entidade
     * @param offset O offset da hitbox.
     */
    void setHitBoxOffset(sf::Vector2f offset);

    /**
     * @brief Atualiza a posição da hitBox de acordo com a posição da entidade
     */
    void atualizaHitBox();

    /**
     * @brief Atualiza estado a da entidade para no componete de física
     * @param noChao noChao true se a entidade estiver no chão, false caso contrário.
     */
    void setNoChao(bool noChao);
    /**
     * @brief Retorna o estado da entidade no componente de física.
     * @return true se a entidade estiver no chão, false caso contrário.
     */
    bool getNoChao() const;

    /**
     * @brief Método virtual para lidar com colisões com outras entidades.
     * 
     * Este método deve ser sobrescrito pelas classes derivadas para definir o comportamento específico quando uma colisão ocorre.
     * @param other Ponteiro para a outra entidade que colidiu.
     */
    virtual void colidiu(Entity* other) = 0;

    /**
     * @brief Método virtual para lidar com colisões com tiles.
     * 
     * Este método deve ser sobrescrito pelas classes derivadas para definir o comportamento específico quando uma colisão com um tile ocorre.
     * @param e Ponteiro para a entidade tile que colidiu.
     */
    virtual void colidiuComTile(Entity* e);

    bool getColisao() const { return colisao;}
};
#endif // _ENTITY_H_