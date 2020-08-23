cmake_minimum_required(VERSION 3.16)

configure_file("config.hpp.in" "config.hpp")

set (sources
    "main.cpp"
)

add_executable(libretro-analyse ${sources} ${RESOURCES})
target_link_libraries(libretro-analyse libretro-core-library)

install(TARGETS libretro-analyse DESTINATION bin)
