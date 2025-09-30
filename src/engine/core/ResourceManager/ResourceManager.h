#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

namespace Gerenciador{
/**
 * @brief Gerencia o carregamento e acesso de recursos, como texturas e fontes.
 * 
 * O ResourceManager é um singleton responsável por carregar, armazenar e fornecer acesso a texturas e fontes
 * usadas no jogo. Ele garante que cada recurso seja carregado apenas uma vez e seja acessível por meio de 
 * um identificador único.
 * 
 * @author Vitor-tml
 */
class ResourceManager{
private:
    static ResourceManager *singleton;                     ///< Instância singleton do gerenciador de recursos
    std::unordered_map<std::string, sf::Texture> texturas; ///< Conjunto de texturas (chave, textura)
    std::unordered_map<std::string, sf::Font> fontes;      ///< Conjunto de fontes (chave, fonte)
    std::unordered_map<std::string, sf::Image> imagens;    ///< Conjunto de fontes (chave, fonte)
    std::unordered_map<std::string, sf::SoundBuffer> sons; ///< Conjunto de sons (chave, som)
    std::unordered_map<std::string, sf::Music*> musicas; ///< Conjunto de músicas (chave, música)
    ResourceManager(){}; ///< Construtora privada para evitar outras instâncias
    ~ResourceManager(){ delete singleton; };
public:

    /**
     * @brief Retorna o ponteiro para a instância singleton do gerenciador
     * @throw Na primeira chamar aloca o gerenciador.
     * @return Ponteiro para a instância.
     */
    static ResourceManager* getInstance();

    ResourceManager(const ResourceManager&) = delete;            ///< Previne cópia.
    ResourceManager& operator=(const ResourceManager&) = delete; ///< Previne atribuição.
    
    /**
     * @brief Carrega textura e armazena com indentificador.
     * @param id identificador da textura a ser usado posteriormente.
     * @param filename Caminho relativo para o arquivo da textura.
     * @note O caminho é relativo ao executável do programa.
     * @return true se a textura foi carregada com sucesso, false caso não.
     */
    bool loadTexture(const std::string& id, const std::string& filename);
    
    /**
     * @brief Carrega fonte e armazena com indentificador.
     * @param id identificador da fonte a ser usado posteriormente.
     * @param filename Caminho relativo para o arquivo da fonte.
     * @note O caminho é relativo ao executável do programa.
     * @return true se a fonte foi carregada com sucesso.
     * @return false se não foi possível carregar a fonte
     */
    bool loadFont(const std::string& id, const std::string& filename);
    
    /**
     * @brief Carrega imagem e armazena com um indentificador
     * @param id identificador da imagem a ser usado posteriormente.
     * @param filename Caminho relativo para o arquivo da fonte.
     * @note O caminho é relativo ao executável do programa.
     * @return true se a imagem foi carregada com sucesso
     * @return false se não foi possível carregar a imagem
     * @todo Adicionar poka-yoke caso a imagem não possa ser carregada
     */
    bool loadImage(const std::string& id, const std::string& filename);

    /**
     * @brief Carrega sons e armazena com um identificador
     * 
     * @param id identificador do som a ser usado posteriormente
     * @param filename caminho relativo para o arquivo do som
     * @return true caso o arquivo seja carregado 
     * @return false caso tenha falhado o carregamento do arquivo 
     */
    bool loadSons(const std::string& id, const std::string& filename);

    /**
     * @brief Retorna uma textura posteriormente carregada, a partir de um identificador.
     * @param id Identificador da textura já armazenada.
     * @return Referência a textura relativa ao ID.
     */
    sf::Texture& getTexture(const std::string& id);
    
    /**
     * @brief Retorna uma fonte posteriormente carregada, a partir de um identificador.
     * @param id Identificador da fonte já armazenada.
     * @return Referência a fonte relativa ao ID.
     */
    sf::Font& getFont(const std::string& id);
    
    /**
     * @brief Retorna uma imagem posteriormente carregada, a partir de um identificador.
     * @param id Identificador da imagem já armazenada.
     * @return Referência a imagem relativa ao ID.
     */
    sf::Image& getImage(const std::string& id);

    /**
     * @brief Retorna um som posteriormente carregado, a partir de um identificador.
     * @param id Identificador do som já armazenado.
     * @return Referência ao som relativa ao ID.
     */
    sf::SoundBuffer& getSom(const std::string& id);


    bool loadMusic(const std::string& id, const std::string& filename);
    sf::Music* getMusic(const std::string& id);
};
}
#endif