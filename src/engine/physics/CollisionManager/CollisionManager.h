#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H

#include "game/entities/Entity/Entity.h"
#include "game/entities/Player/Player.h"
#include <unordered_set>

namespace Gerenciador {

/**
 * @class CollisionManager
 * @brief Gerencia as colisões das entidades.
 * 
 * A classe `CollisionManager` é responsável por verificar se as entidades estão
 * colidindo e chamar os respectivos métodos de tratamento de colisão.
 * 
 * @author Vitor-tml
 */
class CollisionManager {
private:
    std::unordered_set<Entity*> entidades; ///< Conjunto de entidades para verificar colisões

public:
    /**
     * @brief Construtor da classe CollisionManager.
     * 
     * Inicializa uma nova instância da classe `CollisionManager`.
     */
    CollisionManager();

    /**
     * @brief Destruidor da classe CollisionManager.
     * 
     * Limpa os recursos utilizados pela instância da classe `CollisionManager`.
     */
    ~CollisionManager();

    /**
     * @brief Adiciona uma entidade ao gerenciador de colisões.
     * 
     * Este método adiciona uma entidade ao conjunto de entidades gerenciado
     * pelo `CollisionManager` para ser verificada em busca de colisões.
     * @param entity Ponteiro para a entidade a ser adicionada.
     */
    void addEntity(Entity* entity);

    /**
     * @brief Remove uma entidade do gerenciador de colisões.
     * 
     * Este método remove uma entidade do conjunto de entidades gerenciado
     * pelo `CollisionManager`, interrompendo a verificação de colisões para
     * essa entidade.
     * @param entity Ponteiro para a entidade a ser removida.
     */
    void removeEntity(Entity* entity);

    /**
     * @brief Trata as colisões entre entidades.
     * 
     * Este método verifica todas as entidades gerenciadas e processa as colisões
     * detectadas, chamando os métodos de tratamento de colisão apropriados.
     */
    void tratarColisoes();

    /**
     * @brief Verifica se duas entidades estão colidindo.
     * 
     * Este método determina se duas entidades estão colidindo com base em
     * suas caixas de colisão.
     * @param a Ponteiro para a primeira entidade.
     * @param b Ponteiro para a segunda entidade.
     * @return Retorna true se as duas entidades estão colidindo, false caso contrário.
     */
    bool verificaColisao(Entity* a, Entity* b);
};

} // namespace Gerenciador

#endif // _COLLISIONMANAGER_H
