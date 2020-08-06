cmake_minimum_required(VERSION 3.16)

project(retro-menu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Gamepad Svg REQUIRED)

set(LIBRETRO_CORE_INFO_PATH "/usr/share/libretro/info" CACHE PATH "Path to libretro info files")
set(LIBRETRO_CORE_PATH "/usr/lib/libretro" CACHE PATH "Path to libretro cores")
set(LIBRETRO_FIRMWARE_PATH "/usr/share/libretro/system" CACHE PATH "Path to libretro firmware, bioses and etc.")

configure_file("src/config.hpp.in" "config.hpp")

set (sources
    "src/config.hpp"
    "src/desktop-file-searcher.cpp"
    "src/desktop-file-searcher.hpp"
    "src/icon-provider.cpp"
    "src/icon-provider.hpp"
    "src/libretro/core-info.cpp"
    "src/libretro/core-info.hpp"
    "src/libretro/core-library.cpp"
    "src/libretro/core-library.hpp"
    "src/libretro/firmware-info.cpp"
    "src/libretro/firmware-info.hpp"
    "src/libretro/paths.hpp"
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

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Svg)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
