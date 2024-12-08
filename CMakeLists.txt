cmake_minimum_required(VERSION 3.29)
project(LifeGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(LifeGame src/main.cpp
        src/game.cpp
        headers/class.h
        src/cellule.cpp
        src/ihm.cpp
)

# Indique le chemin vers les fichiers include et les bibliothèques de SFML
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Recherche les composants nécessaires de SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Lien avec les bibliothèques SFML
target_link_libraries(LifeGame sfml-system sfml-window sfml-graphics sfml-audio)

# Ajoute le répertoire d'includes de SFML
target_include_directories(LifeGame PRIVATE "C:/SFML/include")

# Ajoute le répertoire contenant json.hpp
target_include_directories(LifeGame PRIVATE "${CMAKE_SOURCE_DIR}/libs/nlohmann/include")
