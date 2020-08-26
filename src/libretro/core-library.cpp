#include <core-library.hpp>
#include <paths.hpp>

using namespace ::libretro;

CoreLibrary::CoreLibrary() {
	for (auto &&core : m_available_cores) {
		core.info = libretro::find_core_info(core, m_core_infos);

		if (core.info)
			m_systemid_mapping[core.info->systemid].emplace_back(core);
	}
}

auto CoreLibrary::info_list() const noexcept -> const core_info_list & {
	return m_core_infos;
}

auto CoreLibrary::available_cores() const noexcept -> const core_list & {
	return m_available_cores;
}

auto CoreLibrary::cores_by_systemid(const string &id) const noexcept -> core_list {
	core_list ret;
	try {
		auto &&list = m_systemid_mapping.at(id);
		for (auto &&v : list)
			ret.emplace_back(v);
	} catch (const std::out_of_range &) {
	}
	return ret;
}

auto libretro::find_core_info(const core &core, const core_info_list &info_list) -> std::optional<core_info> {
	auto item = std::find_if(info_list.cbegin(), info_list.cend(), [&core](const core_info &match) -> bool {
		return core.name == match.name;
	});

	if (item != std::end(info_list))
		return *item;

	return std::nullopt;
}
