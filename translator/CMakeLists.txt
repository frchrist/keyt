cmake_minimum_required(VERSION 3.16)
project(KeyboardTranslator
        VERSION 1.0.0
        DESCRIPTION "AZERTY to QWERTY keyboard translator for Qt"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Test REQUIRED)
include(GNUInstallDirs)

add_library(KeyboardTranslator STATIC
    src/KeyboardTranslator.cpp
    include/KeyboardTranslator.h
)

add_library(KeyboardTranslator::KeyboardTranslator ALIAS KeyboardTranslator)

target_include_directories(KeyboardTranslator
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(KeyboardTranslator
    PUBLIC
        Qt6::Widgets
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "KeyboardTranslatorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/KeyboardTranslatorConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/KeyboardTranslatorConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KeyboardTranslator
)

install(TARGETS KeyboardTranslator
    EXPORT KeyboardTranslatorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/KeyboardTranslator
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT KeyboardTranslatorTargets
    FILE KeyboardTranslatorTargets.cmake
    NAMESPACE KeyboardTranslator::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KeyboardTranslator
)

install(
    FILES
        "${PROJECT_BINARY_DIR}/KeyboardTranslatorConfig.cmake"
        "${PROJECT_BINARY_DIR}/KeyboardTranslatorConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KeyboardTranslator
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

export(EXPORT KeyboardTranslatorTargets
    FILE "${PROJECT_BINARY_DIR}/cmake/KeyboardTranslatorTargets.cmake"
    NAMESPACE KeyboardTranslator::
)
