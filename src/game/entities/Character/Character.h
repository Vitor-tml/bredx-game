#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "game/entities/Entity/Entity.h"

/**
 * @class Character
 * @brief Representa um personagem no jogo.
 * 
 * A classe Character é uma especialização da classe Entity que adiciona atributos de vida e ataque.
 * 
 * @see Entity
 * @see Vitor-tml
 */
class Character : public Entity {
private:
    int vida;   //< Vida do personagem
    int ataque; //< Valor de ataque do personagem

public:
    /**
     * @brief Construtor da classe Character.
     * Inicializa um novo personagem com uma textura, posição, vida e valor de ataque.
     * @param textura Referência para a textura SFML a ser usada pelo personagem.
     * @param x Coordenada no eixo x do personagem.
     * @param y Coordenada no eixo y do personagem.
     * @param life Valor inicial de vida do personagem. O padrão é -1.
     * @param atack Valor inicial de ataque do personagem. O padrão é -1.
     */
    Character(sf::Texture &textura, int x = 0, int y = 0, int life = -1, int atack = -1);

    /**
     * @brief Destrutor da classe Character.
     * O destruidor é virtual para garantir a destruição correta das classes derivadas e está vazio por não ter alocação de recursos.
     */
    virtual ~Character(){};

    /**
     * @brief Executa a lógica do personagem.
     * Este método é chamado a cada frame para atualizar o estado do personagem.
     * @param deltaTime Tempo decorrido desde a última atualização.
     */
    virtual void executar(float deltaTime) override;

    // Métodos de colisão desativados para implementação futura
    // virtual void colidiu(Entity* other) = 0;
    // virtual void colidiuComTile(Entity* e) = 0;
};

#endif // _CHARACTER_H