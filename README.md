# Prodislex Game
Este é um projeto de um jogo de plataforma 2D desenvolvido em C++ com foco em criar uma game engine personalizada que suporte mecânicas complexas de jogos de plataforma.
Também faz parte do projeto a interação entre o desenvolvedor e os artistas responsáveis pela criação de assets visuais e de som, para garantir que o jogo seja atraente.
Código: Vitor-tml
Assets: Brenda Alves
Música: João Manfron
Documentação: https://vitor-tml.github.io/bredx-game/index.html

## Introdução

O objetivo deste projeto é criar um jogo de plataforma com elementos clássicos como saltos, coleta de itens, inimigos, e fases desafiadoras. A engine é desenvolvida do zero, focando em modularidade e eficiência.

## Compilação
### Pré-Requisitos
- **CMAKE**: Certifique-se que o CMAKE está instalado. [Instalar CMake](https://cmake.org/install/).
- **MAKE**: Certifique-se que o MAKE está instalar. [Instalar MAKE](https://gnuwin32.sourceforge.net/packages/make.htm)
- **SFML**: Versão GCC 13.10 MinGW 64bit. [Baixar Biblioteca](https://www.sfml-dev.org/files/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip)

### Passo-a-passo
1.  Clone o repositório.
    ```bash
    git clone https://github.com/Vitor-tml/jogo-de-plataforma-cpp
    cd jogo-de-platforma-cpp
    ```
2. Crie os caminhos necessários.
    
    Pasta da biblioteca
    ```bash
    mkdir libs
    ```
    (mover a pasta do SFML para ```libs```)
    
    Pasta para compilação
    ```bash
    mkdir build
    ```
3. Gere os arquivos de compilação na pastal ```build``` (necessário a cada novo arquivo do projeto).
    ```bash
    cd build
    cmake ..
    ```
4. _Cruze os dedos_ e compile o projeto.
    ```bash
    make -j16
    ```
    ```-j16``` esse parâmetro define quantas threads serão usadas na compilação.
5. Execute o programa.
    
    #### Caso esteja no windows:
    
    1. Copie as dlls da do caminho ```.\libs\SFML-2.6.1\bin\``` para a pasta ```build``` ou outro caminho do executável.    
    2. Execute o programa:
        ```bash
        ./game.exe
        ```
    #### Caso esteja no linux:
    1. Seja feliz.
    2. Execute o programa:
        ```bash
        ./game
        ```
## Estrutura do Projeto

```plaintext
JogoPlataforma/
├── docs
│   ├── html               # Documentação em HTML
│   └── uml                # Diagramas UML
├── include                 # Headers Externos
├── libs                    # Bibliotecas Externas
├── src                     # Código Fonte
│   ├── engine
│   │   ├── Animation       # Sistema de Animação
│   │   ├── CollisionManager # Gerenciamento de Colisões
│   │   ├── Ente            # Implementação de Entidades
│   │   ├── Paralaxe        # Implementação de Paralaxe
│   │   ├── PhysicsComponent # Componentes de Física
│   │   ├── Renderer        # Sistema de Renderização
│   │   ├── ResourceManager  # Gerenciamento de Recursos
│   │   ├── SceneManager    # Gerenciamento de Cenas
│   │   └── TileMap         # Gerenciamento de Mapas de Tiles
│   └── game
│       ├── Entity          # Implementação de Entidades
│       │   └── Character    # Classe Base para Personagens
│       │       └── Player    # Implementação do Jogador
│       └── Scenes          # Implementação das Cenas
│           ├── CreditsScene # Cena de Créditos
│           ├── GameScene    # Cena do Jogo
│           └── MenuScene     # Cena do Menu
└── CMakeLists.txt          # Configuração do CMake


```
## Gerenciamento do Projeto
[Notion](https://buttered-hardhat-d97.notion.site/Prodisgame-9a12f75679a847f8b654f903ab56e048?pvs=4)

## Estado do Jogo
Clique na imagem para abrir o vídeo.
[![Estado do Jogo](https://i.pinimg.com/736x/f1/22/3e/f1223e6ca40966eaeee9ece466791c1c.jpg)](https://youtu.be/8EU4itDEwD0)
