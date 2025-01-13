cmake_minimum_required(VERSION 3.10)
project(Keyboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # Active la génération automatique du moc
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_executable(${PROJECT_NAME}
    main.cpp

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(translator)
target_link_libraries(${PROJECT_NAME} KeyboardTranslator)

find_package(Qt6 COMPONENTS Widgets Test REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Test)
