#pragma once

#include <core-info.hpp>
#include <functional>
#include <optional>

#include <QMap>
#include <QSet>

namespace libretro {

auto find_core_info(const core &core, const core_info_list &info_list) -> std::optional<core_info>;

class CoreLibrary {
public:
	CoreLibrary();

	auto info_list() const noexcept -> const core_info_list &;
	decltype(auto) info_list_all_manufacturers() const noexcept { return m_all_manufacturers; };
	decltype(auto) info_list_all_systemids() const noexcept { return m_all_systemids; };

	auto available_cores() const noexcept -> const core_list &;
	auto cores_by_manufacturer(const string &id) const noexcept -> core_list;
	auto cores_by_systemid(const string &id) const noexcept -> core_list;

	decltype(auto) supported_manufacturer() { return m_available_manufacturers; };
	decltype(auto) supported_systemids() { return m_available_systemids; };

private:
	core_info_list m_core_infos{prepare_core_info_list()};
	core_list m_available_cores{prepare_core_list()};

	string_list m_all_manufacturers;
	string_list m_all_systemids;
	string_list m_available_manufacturers;
	string_list m_available_systemids;

	std::map<string, std::vector<std::reference_wrapper<core>>> m_systemid_mapping;
	std::map<string, std::vector<std::reference_wrapper<core>>> m_manufacturer_mapping;
	std::map<string, string_list> m_manufacturer_to_systemid_mapping;
};
} // namespace libretro
