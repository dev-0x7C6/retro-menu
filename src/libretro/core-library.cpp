#include <core-library.hpp>
#include <paths.hpp>

#include <ranges>
#include <set>
#include <iostream>

using namespace ::libretro;
using namespace std::views;

template <typename list_type, typename T>
auto unique_list(list_type &&list, T core_info::*member) noexcept -> string_list {
	std::set<string> buffer;
	for (auto &&info : list)
		for (auto &&value : (info.*member).split('|'))
			buffer.emplace(value);

	return {buffer.begin(), buffer.end()};
}

CoreLibrary::CoreLibrary() {
	auto &&view = m_core_infos | filter([](const core_info &info) noexcept { return info.is_found; });

	m_all_manufacturers = unique_list(m_core_infos, &core_info::manufacturer);
	m_all_systemids = unique_list(m_core_infos, &core_info::systemid);

	m_available_manufacturers = unique_list(view, &core_info::manufacturer);
	m_available_systemids = unique_list(view, &core_info::systemid);

	for (auto &&core : m_available_cores) {
		core.info = libretro::find_core_info(core, m_core_infos);

		auto &&info = core.info;

		if (!info.has_value())
			continue;

		auto &&systemid = info->systemid;
		auto &&manufacturer = info->manufacturer;

		m_systemid_mapping[systemid].emplace_back(core);
		m_manufacturer_mapping[manufacturer].emplace_back(core);
		m_manufacturer_to_systemid_mapping[manufacturer].append(systemid);
	}
}

auto CoreLibrary::info_list() const noexcept -> const core_info_list & {
	return m_core_infos;
}

auto CoreLibrary::available_cores() const noexcept -> const core_list & {
	return m_available_cores;
}

auto CoreLibrary::cores_by_manufacturer(const string &id) const noexcept -> core_list {
	core_list ret;
	try {
		auto &&list = m_manufacturer_mapping.at(id);
		for (auto &&v : list)
			ret.emplace_back(v);
	} catch (const std::out_of_range &) {
	}
	return ret;
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
