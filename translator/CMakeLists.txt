# CMakeLists.txt principal
cmake_minimum_required(VERSION 3.16)  # Version minimale augmentée pour Qt6
project(KeyboardTranslator)

# Configuration globale
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trouve les packages Qt6 nécessaires
find_package(Qt6 COMPONENTS Widgets Test REQUIRED)

# Crée la bibliothèque KeyboardTranslator
add_library(KeyboardTranslator STATIC
    src/KeyboardTranslator.cpp
    include/KeyboardTranslator.h
)

# Configure les répertoires d'inclusion
target_include_directories(KeyboardTranslator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Lie les bibliothèques Qt6
target_link_libraries(KeyboardTranslator
    PUBLIC
        Qt6::Widgets
)

# Ajoute le sous-répertoire des tests
add_subdirectory(tests)
