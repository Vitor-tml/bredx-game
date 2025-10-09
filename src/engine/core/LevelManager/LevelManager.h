#pragma once

#include <unordered_map>
#include <string>
#include <game/Levels/Level.h>

// Inicio namespace Gerenciador
namespace Gerenciador {
class LevelManager {
private:
    static LevelManager* singleton;

    std::unordered_map<std::string, Level*> niveis;
    Level *nivelAtual;
    LevelManager();
public:
    static LevelManager* getInstance();
    ~LevelManager();

    void inicializar();
    // Func Futuras
    // void registraNivel(Level* nivel);
    // void carregaNivel(std::string id);
    // Level* getNivelAtual() const;

};
} // Fim namespace Gerenciador