#ifndef _PLAYER_H
#define _PLAYER_H

#include "game/entities/Character/Character.h"
#include "engine/graphics/Animation/Animation.h"
/**
 * @class Player
 * @brief Representa o jogador no jogo
 *
 * A classe Player gerencia o comportamento específico do jogador,
 * incluindo movimento horizontal e a habilidade de pular.
 */
class Player : public Character {
private:
    int pontos; ///< Pontos acumulados pelo jogador.
    float velocidadeHorizontal; ///< Velocidade horizontal do jogador.

    Animation walkAnimation;
    Animation idleAnimation;
    Animation* currentAnimation;
    bool isMoving;

public:
    /**
     * @brief Construtor da classe Player.
     * @param textura A textura a ser aplicada ao jogador.
     * @param x Posição inicial X do jogador.
     * @param y Posição inicial Y do jogador.
     * @param life Vida inicial do jogador.
     * @param atack Poder de ataque inicial do jogador.
     * @param points Pontos iniciais do jogador.
     */
    Player(sf::Texture& textura, int x = 0, int y = 0, int life = -1, int atack = -1, int points = 0);

    /**
     * @brief Destrutor da classe Player.
     * Vazia porque não sao alocados recursos dinamicamente.
     */
    ~Player() {};

    /**
     * @brief Atualiza o estado do jogador.
     * 
     * Verifica as entradas do teclado para movimentação e pulo e aplica
     * a física de movimentação ao jogador.
     * @param deltaTime Tempo decorrido desde a última atualização.
     */
    void executar(float deltaTime) override;

    /**
     * @brief Trata colisões do jogador com outras entidades.
     * @param other A outra entidade com a qual o jogador colidiu.
     * @todo implementar a entity->colidiuComPlayer() para todas as entidades
     */
    void colidiu(Entity* other){};

    /**
     * @brief Faz o jogador pular.
     * Chama a função de pulo da física.
    */
    void pular();
};

#endif // _PLAYER_H
