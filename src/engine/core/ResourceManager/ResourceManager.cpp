#include "ResourceManager.h"
#include <iostream>


Gerenciador::ResourceManager* Gerenciador::ResourceManager::singleton = nullptr;
namespace Gerenciador{
ResourceManager* ResourceManager::getInstance()
{
    if(singleton == nullptr)
        singleton = new ResourceManager;

    return singleton;
}

bool ResourceManager::loadTexture(const std::string& id, const std::string& filename){
    sf::Texture textura;
    if(textura.loadFromFile(filename)){
        texturas[id] = textura;
        return true;
    }
    std::cerr << "Erro ao carregar textura: " << filename << std::endl;
    exit(1);         // Fechar o programa se erro
    // return false; // Tratar erro na main
}

sf::Texture& ResourceManager::getTexture(const std::string& id){
    // std::cout << "Carregando textura: " << id << std::endl;
    sf::Texture* placeHolder = new sf::Texture;
    placeHolder->create(64, 64);
    // Colocar tratamento caso não tenha a textura
    if(texturas.find(id) == texturas.end())
    {
        std::cout << "A textura "<< id << " ainda nao foi carregada! Adicionando placeHolder" << std::endl;
        return *placeHolder;
    }
    else
        return texturas.at(id);
}

bool ResourceManager::loadFont(const std::string& id, const std::string& filename)
{
    sf::Font fonte;
    if(fonte.loadFromFile(filename)){
        fontes[id] = fonte;
        return true;
    }
    std::cerr << "Erro ao carregar textura: " << filename << std::endl;
    exit(1);         // Fechar o programa se erro
    // return false; // Tratar erro na main
}

sf::Font& ResourceManager::getFont(const std::string& id)
{
    sf::Font* fonte = new sf::Font;
    // Colocar alguma fonte padrao
    // fonte.setFont();
    if(fontes.find(id) == fontes.end())
    {
        std::cout << "A fonte "<< id << " ainda nao foi carregada!" << std::endl;
        return *fonte;
    }
    else
        return fontes.at(id);
}

bool ResourceManager::loadImage(const std::string& id, const std::string& filename)
{
    // Adicionar poka-yoke se não char a imagem;
    sf::Image imagem;
    if(imagem.loadFromFile(filename)){
        imagens[id] = imagem;
        return true;
    }
    std::cerr << "Erro ao carregar imagem: " << filename << std::endl;
    exit(1); // Colocar tratamento de erro posteriormente
    return false; 
}

sf::Image& ResourceManager::getImage(const std::string& id)
{
    // Colocar retorno de placeHolder caso a imagem não exista
    return imagens.at(id);
}

bool ResourceManager::loadSons(const std::string& id, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if(buffer.loadFromFile(filename)){
        sons[id] = buffer;
        return true;
    }
    std::cerr << "Erro ao carregar som: " << filename  << std::endl;
    return false;
}

sf::SoundBuffer& ResourceManager::getSom(const std::string& id)
{
    return  sons.at(id);
}

bool ResourceManager::loadMusic(const std::string& id, const std::string& filename) {
    sf::Music *nMusica = new sf::Music;
    if (!nMusica->openFromFile(filename))
        return false;
    musicas[id] = nMusica;
    return true;
}

sf::Music* ResourceManager::getMusic(const std::string& id) {
    return musicas.at(id);
}
}// end namespace Gerenciador