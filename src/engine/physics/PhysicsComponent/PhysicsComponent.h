#ifndef _FISICA_H
#define _FISICA_H

#include <SFML/Graphics.hpp>

/**
 * @class PhysicsComponent
 * @brief Gerencia a física aplicada a entidades no jogo.
 * 
 * A classe PhysicsComponent lida com a aplicação de física básica a entidades, 
 * como a gravidade e o impulso do pulo.
 * 
 * @see Vitor-tml
 */
class PhysicsComponent {
private:
    static float gravidade;   //< Gravidade aplicada às entidades
    sf::Vector2f *velocidade; //< Ponteiro para a velocidade da entidade que agrega o componente
    sf::Vector2f *posicao;    //< Ponteiro para a posição da entidade que agrega o componente
    bool estaNoChao;          //< Flag que indica se a entidade está colidindo verticalmente com o topo de uma plataforma
    bool pulando;             //< Flag que indica se a entidade está pulando (utilizada para pulo duplo)
    float forcaPulo;          //<
public:
    /**
     * @brief Construtor do componente de física.
     * 
     * Inicializa o componente de física com ponteiros para a posição e velocidade da entidade.
     * @param position Ponteiro para a posição da entidade.
     * @param speed Ponteiro para a velocidade da entidade.
     */
    PhysicsComponent(sf::Vector2f *position = nullptr, sf::Vector2f *speed = nullptr, float fPulo = 300.f);

    /**
     * @brief Destrutor da classe PhysicsComponent.
     * O destrutor é vazio, pois a classe não aloca recursos dinamicamente.
     */
    ~PhysicsComponent() {}

    /**
     * @brief Aplica física à entidade.
     * 
     * Este método aplica as leis da física, como a gravidade, à entidade durante o tempo delta especificado.
     * @param deltaTime Tempo decorrido desde a última atualização.
     */
    void aplicaFisica(float deltaTime);

    /**
     * @brief Atualiza o estado do componente indicando se a entidade está no chão.
     * 
     * Este método atualiza o estado do componente para refletir se a entidade está ou não em contato com o chão.
     * @param estado Booleano indicando se a entidade está no chão.
     */
    void setNoChao(bool estado);

    /**
     * @brief Retorna o estado da entidade em relação ao chão.
     * @return true se a entidade está no chão, false caso contrário.
     */
    bool getNoChao() const;

    /**
     * @brief Inicia o pulo da entidade.
     * Este método aplica uma força de pulo à entidade, iniciando o movimento de pulo.
     * @param forcaPulo A força aplicada ao pulo.
     */
    void pular(float forcaPulo = 300.f);
};

#endif // _FISICA_H
