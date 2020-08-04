cmake_minimum_required(VERSION 3.16)

project(retro-menu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Gamepad REQUIRED)

set (sources
    "desktop-file-searcher.cpp"
    "desktop-file-searcher.hpp"
    "main.cpp"
    "menu-entry-model.cpp"
    "menu-entry-model.hpp"
    "menu-entry.hpp"
    "pixmap-provider.cpp"
    "pixmap-provider.hpp"
    "process-runner.cpp"
    "process-runner.hpp"
)

option(ENABLE_QT_QUICK_COMPILER OFF)


if (ENABLE_QT_QUICK_COMPILER)
    find_package(Qt5QuickCompiler)
    qtquick_compiler_add_resources(RESOURCES qml.qrc)
else()
    set(RESOURCES qml.qrc)
endif()

add_executable(${PROJECT_NAME} ${sources} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
