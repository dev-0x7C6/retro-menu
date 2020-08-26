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
	auto available_cores() const noexcept -> const core_list &;

	auto cores_by_systemid(const string &id) const noexcept -> core_list;

private:
	core_info_list m_core_infos{prepare_core_info_list()};
	core_list m_available_cores{prepare_core_list()};

	std::map<string, std::vector<std::reference_wrapper<core>>> m_systemid_mapping;
};
} // namespace libretro
