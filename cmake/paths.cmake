set(LIBRETRO_CORE_INFO_PATH_DEFAULT "/usr/share/libretro/info")
set(LIBRETRO_CORE_PATH_DEFAULT "/usr/lib/libretro")
set(LIBRETRO_FIRMWARE_PATH_DEFAULT "/usr/share/libretro/system")

if (DEFINED ENV{LIBRETRO_CORE_INFO_PATH})
    message("-- Setting LIBRETRO_CORE_INFO_PATH_DEFAULT from ENV")
    set(LIBRETRO_CORE_INFO_PATH_DEFAULT $ENV{LIBRETRO_CORE_INFO_PATH})
endif()

if (DEFINED ENV{LIBRETRO_CORE_PATH})
    message("-- Setting LIBRETRO_CORE_PATH_DEFAULT from ENV")
    set(LIBRETRO_CORE_PATH_DEFAULT $ENV{LIBRETRO_CORE_PATH})
endif()

if (DEFINED ENV{LIBRETRO_FIRMWARE_PATH})
    message("-- Setting LIBRETRO_FIRMWARE_PATH_DEFAULT from ENV")
    set(LIBRETRO_FIRMWARE_PATH_DEFAULT $ENV{LIBRETRO_FIRMWARE_PATH})
endif()

set(LIBRETRO_CORE_INFO_PATH "${LIBRETRO_CORE_INFO_PATH_DEFAULT}" CACHE PATH "Path to libretro info files")
set(LIBRETRO_CORE_PATH "${LIBRETRO_CORE_PATH_DEFAULT}" CACHE PATH "Path to libretro cores")
set(LIBRETRO_FIRMWARE_PATH "${LIBRETRO_FIRMWARE_PATH_DEFAULT}" CACHE PATH "Path to libretro firmware, bioses and etc.")

message("-- LIBRETRO_CORE_INFO_PATH value is ${LIBRETRO_CORE_INFO_PATH}")
message("-- LIBRETRO_CORE_PATH value is ${LIBRETRO_CORE_PATH}")
message("-- LIBRETRO_FIRMWARE_PATH value is ${LIBRETRO_FIRMWARE_PATH}")