# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)  # Version minimale augmentée pour Qt6

# Activation du support des tests
enable_testing()

# Configuration pour Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trouve les packages Qt6 nécessaires
find_package(Qt6 COMPONENTS Test Widgets REQUIRED)

# Configuration des tests individuels
set(TEST_FILES
    tst_keyboard_simple.cpp
    tst_keyboard_complex.cpp
    tst_keyboard_events.cpp
)

# Création d'une cible de test pour chaque fichier
foreach(TEST_FILE ${TEST_FILES})
    # Extrait le nom de base du fichier pour nommer le test
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Crée l'exécutable de test
    add_executable(${TEST_NAME} ${TEST_FILE})

    # Configure les propriétés du test
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

    # Lie les bibliothèques nécessaires
    target_link_libraries(${TEST_NAME}
        PRIVATE
            KeyboardTranslator
            Qt6::Test
            Qt6::Widgets
    )

    # Ajoute le test à CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
