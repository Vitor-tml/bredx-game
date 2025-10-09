#pragma once
#include "game/entities/Entity/Entity.h"
#include "vector"
namespace Gerenciador { // Início do namespace Gerenciador

class UpdateManager {
private:
    static UpdateManager *singleton;
    std::vector<Entity*> lEntidades;   
    UpdateManager();
public:
    ~UpdateManager();
    
    static UpdateManager* getInstance();

    void atualiza();
    void registrar(Entity* e);
    void remover(Entity* e);
    void atualizar(float deltaTime);
    void limpar();
    // retorna uma referência constante a um vetor parametrizado para ponteiro de entidade 
    const std::vector<Entity*>& getEntidades();
};

}; // Fim do namespace Gerenciador