#include "LevelManager.h"

// Início namespace Gerenciador
namespace Gerenciador {
LevelManager* LevelManager::singleton = nullptr;

LevelManager::LevelManager() : nivelAtual(nullptr){};

LevelManager* LevelManager::getInstance()
{
    if(!singleton)
    {
        singleton = new LevelManager();
    }
    return singleton;
}

LevelManager::~LevelManager()
{
    delete singleton;
}
void LevelManager::inicializar() {
    nivelAtual = new Level(); // Cria o nível
    nivelAtual->carregarTexturas();
    nivelAtual->carregarMusicas();
    nivelAtual->carregarMapa();
    nivelAtual->carregarEntidades();
    nivelAtual->carregarCenario();
}

} // Fim namespace Gerenciador