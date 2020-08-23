cmake_minimum_required(VERSION 3.16)

project(retro-menu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Gamepad Svg REQUIRED)

include("cmake/paths.cmake")

configure_file("src/config.hpp.in" "config.hpp")

option(LIBRETRO_ANALYSE "Additional tool to sanitize configuration" ON)

add_subdirectory("src/libretro")

if (LIBRETRO_ANALYSE)
    add_subdirectory("src/libretro-analyse")
endif()

set (sources
    "src/config.hpp"
    "src/desktop-file-searcher.cpp"
    "src/desktop-file-searcher.hpp"
    "src/icon-provider.cpp"
    "src/icon-provider.hpp"
    "src/main.cpp"
    "src/menu-entry-model.cpp"
    "src/menu-entry-model.hpp"
    "src/menu-entry.hpp"
    "src/pixmap-provider.cpp"
    "src/pixmap-provider.hpp"
    "src/process-schedule.cpp"
    "src/process-schedule.hpp"
)

option(ENABLE_QT_QUICK_COMPILER OFF)


if (ENABLE_QT_QUICK_COMPILER)
    find_package(Qt5QuickCompiler)
    qtquick_compiler_add_resources(RESOURCES qml.qrc)
else()
    set(RESOURCES qml.qrc)
endif()

add_executable(${PROJECT_NAME} ${sources} ${RESOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Svg libretro-core-library)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
