#include "Renderer.h"
#include <algorithm>
#include <iostream>

namespace Gerenciador{
// Iniciando singleton
Gerenciador::Renderer* Renderer::singleton = nullptr;

Renderer::Renderer(int largura, int altura, const std::string &titulo)
    : janela(sf::VideoMode(largura, altura), titulo),
      camera(sf::FloatRect(0, 0, largura, altura)), // Inicia câmera com tamanho da janela
      caixaDeMovimento(largura / 4, altura / 4, largura / 2, altura / 2) // Define os limites iniciais
{
    janela.setFramerateLimit(60);
    isShader = false;
    
    render(); // Chama render para limpar a janela com a cor preta inicialmente
}

Renderer::~Renderer(){
    delete singleton;
}

Renderer* Renderer::getInstance(int largura, int altura, const std::string& titulo)
{
    if(singleton == nullptr)
        singleton = new Renderer(largura, altura, titulo);
    
    return singleton;
}

void Renderer::addDrawable(const sf::Drawable &drawable, int camada){
    drawables.push_back(std::make_pair(&drawable, camada));
}

void Renderer::clearDrawables(){
    drawables.clear();
}

void Renderer::moveCamera(float x, float y){
    camera.move(x, y);
}

void Renderer::setCentroCamera(float x, float y){
    camera.setCenter(x, y);
}

void Renderer::setTamanhoCamera(float largura, float altura){
    camera.setSize(largura, altura);
}

void Renderer::render()
{
    sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
    janela.clear(sf::Color::Black);
    shader.setUniform("time", deltaTime);
    shader.setUniform("isShader", isShader);
    janela.setView(camera);
    // Ordena os elementos com base na camada
    std::sort(drawables.begin(),
              drawables.end(),
              [](const std::pair<const sf::Drawable *, int> &a, const std::pair<const sf::Drawable *, int> &b)
              {
                  return a.second < b.second;
              });

    // Define os estados de renderização com blending
    sf::RenderStates states;
    states.blendMode = sf::BlendAlpha; // Modo de blending padrão

    for (const auto &drawable : drawables){
        if (shaderCarregado) {
            janela.draw(*drawable.first, &shader);
        } else {
            janela.draw(*drawable.first);
        }
    }

    janela.display();
    clearDrawables();
}

bool Renderer::isOpen(){
    return janela.isOpen();
}

void Renderer::close(){
    janela.close();
}

bool Renderer::pollEvent(sf::Event &evento){
    return janela.pollEvent(evento);
}

sf::Vector2u Renderer::getTamanho() const { 
    return janela.getSize();
}

void Renderer::carregarShaders()
{   
    std::string  path = "../assets/shaders/shader.frag";
    if (shader.loadFromFile(path, sf::Shader::Fragment)) {
        shaderCarregado = true;
    } else {
        std::cerr << "Erro ao carregar shaders: " << path << std::endl;
        shaderCarregado = false;
    }
    isShader = true;
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("resolution", sf::Vector2f(janela.getSize().x, janela.getSize().y));
}

void Renderer::tirarShader()
{
    setIsShader(false);
}

void Renderer::setMoveBounds(const sf::FloatRect& bounds) {
    caixaDeMovimento = bounds;
}

void Renderer::updateCamera(const sf::Vector2f& playerPos) {
    float offsetY = 300.0f; // Valor positivo para mover o personagem para cima na tela
    // Atualiza a posição da caixaDeMovimento
    caixaDeMovimento.left = camera.getCenter().x - caixaDeMovimento.width / 2;
    caixaDeMovimento.top = camera.getCenter().y - caixaDeMovimento.height / 2 + offsetY;

    if (isPlayerOutsideBounds(playerPos)) {
        // Calcule a nova posição da câmera suavemente
        sf::Vector2f targetPosition = playerPos; // Posição do jogador
        targetPosition.y -= offsetY;
        sf::Vector2f currentPosition = camera.getCenter(); // Posição atual da câmera
        
        // Interpolação linear para mover a câmera suavemente
        float smoothFactor = 0.1f; // Ajuste este valor para controlar a suavidade
        sf::Vector2f newPosition = currentPosition + (targetPosition - currentPosition) * smoothFactor;

        // Ajuste a posição da câmera para que o jogador fique mais abaixo do centro
        
        setCentroCamera(newPosition.x, newPosition.y);
    }

    // // Cria a representação visual da caixa
    // sf::RectangleShape *caixaCam = new sf::RectangleShape(sf::Vector2f(caixaDeMovimento.width, caixaDeMovimento.height));
    // caixaCam->setPosition(caixaDeMovimento.left, caixaDeMovimento.top);
    // caixaCam->setFillColor(sf::Color::Transparent); // Vermelho com transparência
    // caixaCam->setOutlineColor(sf::Color::Yellow);
    // caixaCam->setOutlineThickness(1);
    // // Adicione a caixaCam à lista de objetos desenháveis
    // addDrawable(*caixaCam, 3); // A camada pode ser ajustada conforme necessário
    
}




sf::View& Renderer::getView() {
    return camera;
}

bool Renderer::isPlayerOutsideBounds(const sf::Vector2f& playerPos) const {
    return playerPos.x < caixaDeMovimento.left || playerPos.x > caixaDeMovimento.left + caixaDeMovimento.width ||
           playerPos.y < caixaDeMovimento.top || playerPos.y > caixaDeMovimento.top + caixaDeMovimento.height;
}
}
