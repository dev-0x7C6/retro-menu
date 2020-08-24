#include <core-library.hpp>
#include <paths.hpp>

using namespace ::libretro;

auto CoreLibrary::info_list() const noexcept -> const core_info_list & {
	return m_core_infos;
}

auto CoreLibrary::available_cores() const noexcept -> const core_list & {
	return m_available_cores;
}

auto CoreLibrary::core_info(const core &sample) const noexcept -> std::optional<libretro::core_info> {
	return libretro::find_core_info(sample, m_core_infos);
}

auto libretro::find_core_info(const core &core, const core_info_list &info_list) -> std::optional<core_info> {
	auto item = std::find_if(info_list.cbegin(), info_list.cend(), [&core](const core_info &match) -> bool {
		return core.name == match.name;
	});

	if (item != std::end(info_list))
		return *item;

	return std::nullopt;
}
