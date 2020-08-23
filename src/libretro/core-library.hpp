#pragma once

#include <core-info.hpp>
#include <functional>

#include <QMap>
#include <QSet>

namespace libretro {

class CoreLibrary {
public:
	auto info_list() noexcept -> const core_info_list &;
	auto available_cores() noexcept -> const core_list &;

private:
	core_info_list m_core_infos{prepare_core_info_list()};
	core_list m_available_cores{prepare_core_list()};
};
} // namespace libretro
