#include "CollisionManager.h"
#include <iostream>

namespace Gerenciador{
CollisionManager::CollisionManager()
{
    entidades.clear();
}
CollisionManager::~CollisionManager()
{
    entidades.clear();
}

void CollisionManager::addEntity(Entity* entity)
{
    if(entity == nullptr){
        std::cout << "Ponteiro nulo, nao foi possivel adicionar entidade!" << std::endl;
    } 
    entidades.insert(entity);
}


void CollisionManager::removeEntity(Entity* entity)
{
    if(entity == nullptr){
        std::cout << "Ponteiro nulo, nao foi possivel remover entidade!" << std::endl;
        return;
    }

    entidades.erase(entity);
}

void CollisionManager::tratarColisoes()
{
    for(auto& entidade : entidades){
        entidade->setNoChao(false);
        for(auto& outra : entidades){
            if(entidade != outra){
                if(verificaColisao(entidade, outra)){
                    entidade->colidiu(outra);
                    outra->colidiu(entidade);
                }
            }
        }
    }
}

bool CollisionManager::verificaColisao(Entity* a, Entity* b)
{
    return a->getHitBox().getGlobalBounds().intersects(b->getHitBox().getGlobalBounds());
}

}