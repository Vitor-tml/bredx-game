#include "UpdateManager.h"

Gerenciador::UpdateManager* Gerenciador::UpdateManager::singleton = nullptr;
namespace Gerenciador
{

UpdateManager::UpdateManager(){}
UpdateManager::~UpdateManager(){ delete singleton;}
UpdateManager* UpdateManager::getInstance()
{
    if(!singleton)
    {
        singleton = new UpdateManager();
    }
    return singleton;
}


} // namespace Gerenciador