set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file("config.hpp.in" "config.hpp")

set (libretro-library-sources
	"core-info.cpp"
	"core-info.hpp"
	"core-library.cpp"
	"core-library.hpp"
	"firmware-info.cpp"
	"firmware-info.hpp"
	"paths.hpp"
)

add_library(libretro-core-library ${libretro-library-sources})

target_include_directories(libretro-core-library PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libretro-core-library PUBLIC Qt5::Core)
