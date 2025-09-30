# Versão mínima requerida do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(game)

# Definir a versão do C++ utilizada
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir o diretório onde o SFML está instalado
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/lib/cmake/SFML")

# Mensagem para verificar os diretórios
message(STATUS "SFML_DIR: ${SFML_DIR}")

# Incluir diretórios de inclusão
include_directories(include)
include_directories(src)
include_directories(${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/Box2D/include)

# Definir o CMAKE_PREFIX_PATH para encontrar as bibliotecas
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${SFML_DIR}")

# Encontrar e carregar os pacotes SFML
find_package(SFML 2.6.1 REQUIRED COMPONENTS system window graphics network audio)

# Buscar automaticamente todos os .cpp e .h dentro de src/ e include/
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE ALL_HEADERS CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

# Criar executável
add_executable(game ${ALL_SOURCES} ${ALL_HEADERS})

# Propriedades do target
set_target_properties(game PROPERTIES 
    WIN32_EXECUTABLE OFF  # Garante que seja um aplicativo de console
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Vincular as bibliotecas SFML
target_link_libraries(game 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)

# Copiar as DLLs para o diretório de saída (Windows)
if (WIN32)
    message(STATUS "Detectado Sistema Windows. Copiando DLLs")
    message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
    message(STATUS "TARGET_FILE_DIR: $<TARGET_FILE_DIR:game>")
    
    set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin")
    message(STATUS "SFML_BIN_DIR: ${SFML_BIN_DIR}")
    
    # Verificar se o diretório existe
    if(EXISTS "${SFML_BIN_DIR}")
        message(STATUS "Diretório SFML bin EXISTE")
    else()
        message(WARNING "Diretório SFML bin NÃO EXISTE: ${SFML_BIN_DIR}")
    endif()
    
    set(SFML_DLLS
        "openal32.dll"
        "sfml-audio-2.dll"
        "sfml-audio-d-2.dll"
        "sfml-graphics-2.dll"
        "sfml-graphics-d-2.dll"
        "sfml-network-2.dll"
        "sfml-network-d-2.dll"
        "sfml-system-2.dll"
        "sfml-system-d-2.dll"
        "sfml-window-2.dll"
        "sfml-window-d-2.dll"
    )
    
    foreach(DLL ${SFML_DLLS})
        set(DLL_PATH "${SFML_BIN_DIR}/${DLL}")
        if(EXISTS "${DLL_PATH}")
            message(STATUS "Encontrado: ${DLL}")
            add_custom_command(TARGET game POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Copiando ${DLL}..."
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DLL_PATH}"
                    "$<TARGET_FILE_DIR:game>"
                COMMENT "Copiando ${DLL}"
            )
        else()
            message(WARNING "DLL NÃO encontrada: ${DLL_PATH}")
        endif()
    endforeach()
endif()
# Configurações de debug/release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build tipo: Debug")
    target_compile_definitions(game PRIVATE DEBUG_BUILD)
endif()

# Avisos do compilador
if(MSVC)
    target_compile_options(game PRIVATE /W4)
else()
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Mensagem final
message(STATUS "CMake configurado com sucesso!")
message(STATUS "Para compilar: make -j4")
message(STATUS "Para executar: ./game")
