#pragma once

#include "engine/graphics/Renderer/Renderer.h"
#include "engine/physics/CollisionManager/CollisionManager.h"
#include "game/entities/Entity/Entity.h"
#include "game/entities/Player/Player.h"
#include "engine/world/TileMap/TileMap.h"
#include "engine/core/SceneManager/SceneManager.h"
#include "game/Scenes/GameScene/GameScene.h"
#include "game/Scenes/MenuScene/MenuScene.h"
#include <vector>

/**
 * @class Game
 * @brief Gerencia o fluxo principal do jogo.
 * 
 * A classe `Game` é responsável por coordenar a renderização, o gerenciamento de colisões,
 * e a manipulação de entidades e mapas. Ela controla a execução do jogo e gerencia o
 * estado e as interações entre diferentes componentes do jogo.
 */
class Game
{
private:
    Gerenciador::Renderer *janela;           ///< Ponteiro para o renderizador (Renderer)
    SceneManager *gCenas;
    GameScene *cenaJogo;
public:
    /**
     * @brief Construtor da classe Game.
     * 
     * Inicializa uma nova instância da classe `Game`, configurando os componentes
     * principais do jogo, incluindo o renderizador, o gerenciador de colisões, o mapa,
     * e o jogador.
     */
    Game();

    /**
     * @brief Destruidor da classe Game.
     * 
     * Limpa os recursos utilizados pela instância da classe `Game`, incluindo a
     * destruição de entidades e outros componentes.
     */
    ~Game();

    /**
     * @brief Executa o loop principal do jogo.
     * 
     * Este método gerencia o ciclo de vida do jogo, incluindo a atualização do estado
     * do jogo, a detecção e tratamento de colisões, e a renderização dos elementos
     * gráficos na tela.
     */
    void executar();
};
