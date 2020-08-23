#include <core-library.hpp>
#include <paths.hpp>

using namespace ::libretro;

auto CoreLibrary::info_list() noexcept -> const core_info_list & {
	return m_core_infos;
}

auto CoreLibrary::available_cores() noexcept -> const core_list & {
	return m_available_cores;
}
